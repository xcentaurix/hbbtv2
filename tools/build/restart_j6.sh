B=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/wpewebkit_%.bbappend
sed -i 's|^PARALLEL_MAKE = "-j 8 -k 0"|PARALLEL_MAKE = "-j 6 -k 0"|' $B
grep -n 'PARALLEL_MAKE' $B
echo "OOM kills in dmesg: $(dmesg 2>/dev/null | grep -ci 'out of memory\|killed process')"
echo "objects done: $(find /home/alpha/wpe-src/build -name '*.o' -newermt '2026-09-20 00:30' | wc -l)"
pgrep -a 'ninja|bitbake|cc1plus' | cut -c1-70 | head -3; echo "(no leftovers expected above)"
cd /home/alpha
setsid nohup bash /home/alpha/bb.sh wpewebkit > /home/alpha/wpe-build16.log 2>&1 < /dev/null &
sleep 5; echo started
