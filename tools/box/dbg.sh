#!/bin/sh
# Debug run: wrap WPEWebProcess to log how it exits, then run wpe_shot in a few configurations.
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test
LX=/media/hdd/wpe-test/libexec/wpe-webkit-2.0

# install the logging wrapper once (real binary kept as .real)
if [ ! -e $LX/WPEWebProcess.real ]; then
  mv $LX/WPEWebProcess $LX/WPEWebProcess.real
  cat > $LX/WPEWebProcess <<'EOF'
#!/bin/sh
"$0.real" "$@"
rc=$?
echo "$(date +%T) WPEWebProcess exit status $rc (128+N means killed by signal N)" >> /tmp/wpe-web.log
exit $rc
EOF
  chmod +x $LX/WPEWebProcess $LX/WPEWebProcess.real
fi

run() {
  label="$1"; shift
  echo "##### $label"
  rm -f /tmp/wpe-web.log
  env "$@" timeout 60 /media/hdd/wpe-test/bin/wpe_shot - /media/hdd/wpe-test/shot_dbg.ppm 2>&1 | grep -vE "headless display connected|WPE WebKit 2|view 1280|load_html issued|no EGL display from WPE"
  echo "--- web process log:"; cat /tmp/wpe-web.log 2>/dev/null || echo "(none)"
  echo "--- dmesg tail:"; dmesg | tail -4
}

run "default (GPU compositing)" X=1
run "CPU painting" WEBKIT_SKIA_ENABLE_CPU_RENDERING=1
