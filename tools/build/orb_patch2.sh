#!/bin/bash
# Polyfill fix: Broadcast.setPresentationSuspended must not throw for a broadcast-independent application.
set -euo pipefail
cd /home/alpha/orb
LAYER=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/orb/files
git checkout -q -- src/bridge.js
python3 - <<'PY'
p = "src/bridge.js"
s = open(p).read()
old = '''    exported.setPresentationSuspended = function(presentationSuspended) {
        hbbtv.native.request('Broadcast.setPresentationSuspended', {
            presentationSuspended: presentationSuspended,
        });
    };
'''
new = '''    exported.setPresentationSuspended = function(presentationSuspended) {
        try {
            hbbtv.native.request('Broadcast.setPresentationSuspended', {
                presentationSuspended: presentationSuspended,
            });
        } catch (e) {
            // A broadcast-independent application has no broadcast presentation to suspend or resume: that is not an
            // error for the caller. Letting the SecurityError escape broke A/V control stop() (and with it applications
            // that stop a preview before starting the film, e.g. the ZDFmediathek: "MediaLibrary Error 666").
            if (e.name !== 'SecurityError') {
                throw e;
            }
        }
    };
'''
assert s.count(old) == 1
open(p, "w").write(s.replace(old, new))
print("patched", p)
PY
{
  echo "From: HbbTV2 experiment <noreply@localhost>"
  echo "Subject: [PATCH] bridge: setPresentationSuspended is a no-op for a broadcast-independent application"
  echo
  echo "ORB answers Broadcast.setPresentationSuspended with SecurityError for an application that was not launched from the"
  echo "broadcast AIT, and the SecurityError escaped from A/V control stop(). Applications that stop a running preview before"
  echo "starting the main video (ZDFmediathek) then failed with their generic media error."
  echo
  echo "---"
  git diff --no-color -- src/bridge.js
} > "$LAYER/0002-bridge-setPresentationSuspended-no-throw-when-broadcast-independent.patch"
make build ORB_NATIVE=rdk BBC_API_ENABLE=0 2>&1 | tail -3
ls -la out/resources/assets/polyfill/hbbtv.js | awk '{print $5, $NF}'
grep -c "broadcast presentation to suspend" out/resources/assets/polyfill/hbbtv.js
