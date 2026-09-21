/*
 * debug.js - forwards what an HbbTV application does to the embedder's log through wpeBridge.log() (a fire-and-forget
 * extension of the bridge, see orb_ext.c): console output, script errors, media element events, canPlayType() and Media
 * Source Extensions probes. Injected at document start in the top frame, before the ORB polyfill.
 */
(function () {
    if (typeof wpeBridge === 'undefined' || typeof wpeBridge.log !== 'function')
        return;

    var seen = {};
    function send(kind, parts) {
        try {
            var text = kind + ' ' + Array.prototype.map.call(parts, function (a) {
                if (typeof a === 'string')
                    return a;
                try { return JSON.stringify(a); } catch (e) { return String(a); }
            }).join(' ');
            if (text.indexOf('[RDK-Native') >= 0 || text.indexOf('[ORB') === 0)
                return; // the polyfill's own chatter
            wpeBridge.log(text.slice(0, 700));
        } catch (e) { }
    }

    ['log', 'info', 'warn', 'error', 'debug'].forEach(function (k) {
        var original = console[k];
        console[k] = function () {
            send('console.' + k, arguments);
            return original.apply(console, arguments);
        };
    });
    window.addEventListener('error', function (e) {
        var t = e.target;
        if (t && t !== window && t.tagName) // a resource that did not load (script, stylesheet, image, ...): say which one
            send('resource error', [t.tagName, t.src || t.href || t.currentSrc || '(no url)']);
        else
            send('window.onerror', [e.message, (e.filename || '') + ':' + e.lineno + ':' + e.colno, e.error && e.error.stack ? e.error.stack.split('\n').slice(0, 3).join(' | ') : '']);
    }, true);
    // applications often turn a rejected promise into their own error state; say what the rejection was (bounded)
    var caught = 0;
    var promiseCatch = Promise.prototype.catch;
    Promise.prototype.catch = function (handler) {
        if (typeof handler !== 'function')
            return promiseCatch.apply(this, arguments);
        return promiseCatch.call(this, function (reason) {
            if (caught++ < 60)
                send('promise.catch', [String(reason && (reason.stack || reason.message || reason)).slice(0, 500)]);
            return handler.apply(this, arguments);
        });
    };
    window.addEventListener('unhandledrejection', function (e) { send('unhandledrejection', [String(e.reason && e.reason.stack || e.reason)]); });

    // media elements: their events do not bubble, so listen in the capture phase
    ['loadstart', 'loadedmetadata', 'loadeddata', 'canplay', 'playing', 'play', 'pause', 'waiting', 'stalled', 'suspend', 'error', 'ended', 'seeking', 'seeked', 'abort', 'emptied', 'ratechange']
        .forEach(function (name) {
            document.addEventListener(name, function (e) {
                var v = e.target;
                if (!v || !v.tagName || !/^(VIDEO|AUDIO)$/.test(v.tagName))
                    return;
                send('media:' + name, [(v.currentSrc || v.src || '(no src)').slice(0, 160), 't=' + v.currentTime.toFixed(2), 'rs=' + v.readyState, 'ns=' + v.networkState,
                    v.videoWidth + 'x' + v.videoHeight, v.error ? 'ERROR ' + v.error.code + ':' + v.error.message : '']);
            }, true);
        });

    var play = HTMLMediaElement.prototype.play;
    HTMLMediaElement.prototype.play = function () {
        send('media.play()', [(this.currentSrc || this.src || '(no src)').slice(0, 160)]);
        var result = play.apply(this, arguments);
        if (result && result.catch)
            result.catch(function (e) { send('media.play() REJECTED', [e && e.name, e && e.message]); });
        return result;
    };

    var canPlayType = HTMLMediaElement.prototype.canPlayType;
    HTMLMediaElement.prototype.canPlayType = function (type) {
        var r = canPlayType.call(this, type);
        var key = 'cpt' + type + r;
        if (!seen[key]) { seen[key] = 1; send('canPlayType', [type, '->', JSON.stringify(r)]); }
        return r;
    };

    if (window.MediaSource) {
        var isTypeSupported = MediaSource.isTypeSupported;
        MediaSource.isTypeSupported = function (type) {
            var r = isTypeSupported.call(MediaSource, type);
            var key = 'its' + type + r;
            if (!seen[key]) { seen[key] = 1; send('MediaSource.isTypeSupported', [type, '->', r]); }
            return r;
        };
        var addSourceBuffer = MediaSource.prototype.addSourceBuffer;
        MediaSource.prototype.addSourceBuffer = function (type) {
            send('MediaSource.addSourceBuffer', [type]);
            try { return addSourceBuffer.apply(this, arguments); } catch (e) { send('MediaSource.addSourceBuffer THREW', [e.name, e.message]); throw e; }
        };
        var appendBuffer = SourceBuffer.prototype.appendBuffer;
        var appended = 0;
        SourceBuffer.prototype.appendBuffer = function (data) {
            if (appended++ < 3 || appended % 50 === 0)
                send('SourceBuffer.appendBuffer', ['#' + appended, (data && data.byteLength) + ' bytes']);
            return appendBuffer.apply(this, arguments);
        };
    } else
        send('MediaSource', ['NOT AVAILABLE']);

    // the geometry the page sees, once loaded and again a few seconds later (HbbTV applications are laid out for 1280x720; one that sizes
    // itself from screen.width or devicePixelRatio would come out too large): window, screen, pixel ratio, document and scrollbars
    function geometry(when) {
        var d = document.documentElement, b = document.body;
        send('viewport ' + when, ['inner ' + window.innerWidth + 'x' + window.innerHeight, 'outer ' + window.outerWidth + 'x' + window.outerHeight,
            'screen ' + screen.width + 'x' + screen.height + ' avail ' + screen.availWidth + 'x' + screen.availHeight, 'dpr ' + window.devicePixelRatio,
            'client ' + d.clientWidth + 'x' + d.clientHeight, 'scroll ' + d.scrollWidth + 'x' + d.scrollHeight + (b ? ' body ' + b.scrollWidth + 'x' + b.scrollHeight : ''),
            'overflow ' + getComputedStyle(d).overflow + '/' + (b ? getComputedStyle(b).overflow : '-'), 'zoom ' + (b ? getComputedStyle(b).zoom : '-')]);
    }
    if (window === window.top) {
        window.addEventListener('load', function () { geometry('load'); setTimeout(function () { geometry('+4s'); }, 4000); });
    }

    // does the document overflow the view (the reason for scrollbars)? Log every change of that, for the first 30 s of a document
    if (window === window.top) {
        var lastOverflow = '', started = Date.now();
        var overflowTimer = setInterval(function () {
            var d = document.documentElement;
            var state = (d.scrollWidth > d.clientWidth ? 'H' : '-') + (d.scrollHeight > d.clientHeight ? 'V' : '-');
            if (state !== lastOverflow) {
                lastOverflow = state;
                send('overflow ' + state, ['scroll ' + d.scrollWidth + 'x' + d.scrollHeight, 'client ' + d.clientWidth + 'x' + d.clientHeight, '+' + (Date.now() - started) + ' ms']);
            }
            if (Date.now() - started > 30000)
                clearInterval(overflowTimer);
        }, 100);
    }

    send('debug.js', ['installed in', location.href]);
})();
