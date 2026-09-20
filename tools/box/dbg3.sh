#!/bin/sh
# Run the web process under the box's gdb (no symbols loaded, to keep memory low) and dump a backtrace at the crash.
. /media/hdd/wpe-test/env.sh
cd /media/hdd/wpe-test
LX=/media/hdd/wpe-test/libexec/wpe-webkit-2.0
GDB=$(which gdb)
echo "gdb: $GDB  ($($GDB --version | head -1))"
cat > $LX/WPEWebProcess <<'EOF'
#!/bin/sh
exec /usr/bin/env gdb -q -batch \
  -ex "set pagination off" -ex "set confirm off" \
  -ex "handle SIGPIPE nostop noprint pass" -ex "handle SIG32 nostop noprint pass" -ex "handle SIG33 nostop noprint pass" \
  -ex run \
  -ex "echo \n==== CRASH: signal/thread ====\n" -ex "info program" -ex "thread" \
  -ex "echo \n==== BACKTRACE (crashing thread) ====\n" -ex "bt 30" \
  -ex "echo \n==== REGISTERS ====\n" -ex "info registers" \
  -ex "echo \n==== x/16i \$pc-32 ====\n" -ex "x/16i \$pc-32" \
  -ex "echo \n==== STACK ====\n" -ex "x/500wx \$sp" \
  -ex "echo \n==== SHARED LIBS ====\n" -ex "info sharedlibrary" \
  --args "$0.real" "$@"
EOF
chmod +x $LX/WPEWebProcess
timeout 120 /media/hdd/wpe-test/bin/wpe_shot - /media/hdd/wpe-test/shot_dbg.ppm > /tmp/wpe-gdb-out.txt 2>&1
echo "exit: $?  output lines: $(wc -l < /tmp/wpe-gdb-out.txt)"
