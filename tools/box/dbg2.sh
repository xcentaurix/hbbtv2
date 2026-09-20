#!/bin/sh
# Re-arm the web-process wrapper with the crash tracer, run wpe_shot once, leave the report in /tmp/wpe-crash.txt
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test
LX=/media/hdd/wpe-test/libexec/wpe-webkit-2.0
cat > $LX/WPEWebProcess <<'EOF'
#!/bin/sh
LD_PRELOAD=/media/hdd/wpe-test/lib/libsegvtrace.so "$0.real" "$@"
rc=$?
echo "$(date +%T) WPEWebProcess exit status $rc" >> /tmp/wpe-web.log
exit $rc
EOF
chmod +x $LX/WPEWebProcess
rm -f /tmp/wpe-crash.txt /tmp/wpe-web.log
timeout 60 /media/hdd/wpe-test/bin/wpe_shot - /media/hdd/wpe-test/shot_dbg.ppm 2>&1 | grep -E "load-changed|TERMINATED|RESULT|snapshot|exit code"
echo "--- $(wc -l < /tmp/wpe-crash.txt 2>/dev/null || echo 0) lines in crash report"
