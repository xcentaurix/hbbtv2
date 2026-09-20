#!/bin/sh
# Run the web process under gdb with the dprintf EGL/GL call trace (trace.gdb).
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test
LX=/media/hdd/wpe-test/libexec/wpe-webkit-2.0
cat > $LX/WPEWebProcess <<'EOF'
#!/bin/sh
exec /usr/bin/env gdb -q -batch -x /media/hdd/wpe-test/trace.gdb --args "$0.real" "$@"
EOF
chmod +x $LX/WPEWebProcess
timeout 150 /media/hdd/wpe-test/bin/wpe_shot - /media/hdd/wpe-test/shot_dbg.ppm > /tmp/wpe-trace-out.txt 2>&1
echo "exit: $?  lines: $(wc -l < /tmp/wpe-trace-out.txt)"
