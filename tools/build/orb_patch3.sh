#!/bin/bash
# Polyfill fix: A/V control removeAttribute('data') referenced undeclared `priv` and `value` (ReferenceError).
set -euo pipefail
cd /home/alpha/orb
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/orb/files
git checkout -q -- src/objects/avcontrol.js
python3 - <<'PY'
p = "src/objects/avcontrol.js"
s = open(p).read()
old = '''    prototype.removeAttribute = function(name) {
        if (name === 'data') {
            delete privates.get(this).data;
            if (priv.playState !== PLAY_STATE_STOPPED) {
                this.stop();
            }
            if (value !== this.data) {
                priv.seekPos = undefined;
                priv.connected = false;
                setMediaSettings.call(this, priv.MediaSettingsConfiguration);
            }
        }
        Element.prototype.removeAttribute.apply(this, arguments);
    };
'''
new = '''    prototype.removeAttribute = function(name) {
        if (name === 'data') {
            const priv = privates.get(this);
            if (priv.playState !== PLAY_STATE_STOPPED) {
                this.stop();
            }
            if (priv.data !== undefined) {
                delete priv.data;
                priv.seekPos = undefined;
                priv.connected = false;
                setMediaSettings.call(this, priv.MediaSettingsConfiguration);
            }
        }
        Element.prototype.removeAttribute.apply(this, arguments);
    };
'''
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
print("patched", p)
PY
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] avcontrol: removeAttribute('data') used undeclared variables"
  echo
  echo "removeAttribute('data') referenced 'priv' and 'value', which are not declared in that function, so it always threw a"
  echo "ReferenceError. Applications that remove the data attribute while resetting the player (ZDFmediathek) then failed with their"
  echo "generic media error (666) when starting the next video."
  echo
  echo "---"
  git diff --no-color -- src/objects/avcontrol.js
} > "$LAYER/0003-avcontrol-removeAttribute-data-undeclared-variables.patch"
make build ORB_NATIVE=rdk BBC_API_ENABLE=0 2>&1 | tail -3
ls -la out/resources/assets/polyfill/hbbtv.js | awk '{print $5, $NF}'
grep -c "priv.data !== undefined" out/resources/assets/polyfill/hbbtv.js
grep -c "delete privates.get(this).data" out/resources/assets/polyfill/hbbtv.js || true
