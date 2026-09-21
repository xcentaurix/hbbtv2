/*
 * jsprof.js - how much time does the page's own JavaScript take? (experiment: replaces debug.js in a private copy of the orb directory, see
 * ua_orbdir.sh + AB_DEBUGJS=1 in ua_ab.sh). Wraps everything that runs page code as its own task (requestAnimationFrame, setTimeout/setInterval, event
 * listeners, MessagePort.onmessage = React's scheduler) and adds up the wall time spent in the wrappers. Microtasks (promise reactions) run after a
 * wrapped callback returns and are NOT counted: the result is a lower bound. Reports from the first key press to 4 s after the last one.
 */
(function () {
    if (typeof wpeBridge === 'undefined' || typeof wpeBridge.log !== 'function' || window !== window.top) return;
    var busy = 0, calls = 0, byKind = {}, startBusy = null, startT = 0, startCalls = 0, startKind = null, timer = 0;
    var st = window.setTimeout, now = function () { return performance.now(); };
    function wrap(fn, kind) {
        if (typeof fn !== 'function') return fn;
        if (fn.__jsprof) return fn.__jsprof;
        var w = function () {
            var s = now();
            try { return fn.apply(this, arguments); }
            finally { var d = now() - s; busy += d; calls++; byKind[kind] = (byKind[kind] || 0) + d; }
        };
        try { Object.defineProperty(fn, '__jsprof', { value: w }); } catch (e) { }
        return w;
    }
    var raf = window.requestAnimationFrame;
    window.requestAnimationFrame = function (cb) { return raf.call(window, wrap(cb, 'raf')); };
    ['setTimeout', 'setInterval'].forEach(function (name) {
        var orig = window[name];
        window[name] = function (cb) { var a = Array.prototype.slice.call(arguments); a[0] = typeof cb === 'function' ? wrap(cb, name) : cb; return orig.apply(window, a); };
    });
    var ael = EventTarget.prototype.addEventListener, rel = EventTarget.prototype.removeEventListener;
    EventTarget.prototype.addEventListener = function (type, l, o) {
        if (typeof l === 'function') l = wrap(l, 'event:' + (type === 'message' ? 'message' : type === 'keydown' ? 'keydown' : 'other'));
        return ael.call(this, type, l, o);
    };
    EventTarget.prototype.removeEventListener = function (type, l, o) { return rel.call(this, type, l && l.__jsprof ? l.__jsprof : l, o); };
    try {
        var d = Object.getOwnPropertyDescriptor(MessagePort.prototype, 'onmessage');
        Object.defineProperty(MessagePort.prototype, 'onmessage', { get: d.get, set: function (f) { d.set.call(this, wrap(f, 'onmessage')); }, configurable: true });
    } catch (e) { }
    function report() {
        var kinds = [];
        for (var k in byKind) kinds.push(k + '=' + Math.round(byKind[k] - (startKind[k] || 0)) + 'ms');
        wpeBridge.log('JSPROF window ' + Math.round(now() - startT) + ' ms wall: page callbacks ' + Math.round(busy - startBusy) + ' ms in ' + (calls - startCalls) + ' calls (' + kinds.join(', ') + ')');
        startBusy = null;
    }
    ael.call(window, 'keydown', function () {
        if (startBusy === null) { startBusy = busy; startT = now(); startCalls = calls; startKind = JSON.parse(JSON.stringify(byKind)); }
        clearTimeout(timer);
        timer = st.call(window, report, 4000);
    }, true);
    wpeBridge.log('JSPROF installed');
})();
