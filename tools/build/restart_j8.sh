B=/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-browser/wpewebkit/wpewebkit_%.bbappend
echo "nproc=$(nproc)"
grep -n 'PARALLEL_MAKE' $B
sed -i 's|^PARALLEL_MAKE = "-j 4 -k 0"|PARALLEL_MAKE = "-j 8 -k 0"|' $B
grep -n 'PARALLEL_MAKE' $B
echo "objects before: $(find /home/alpha/wpe-src/build -name '*.o' -newermt '2026-09-20 00:30' | wc -l)"
pkill -TERM -f "bb.sh wpewebkit"; sleep 1
pkill -TERM -f "bitbake" ; sleep 2
pkill -TERM ninja; sleep 3
pgrep -a 'ninja|bitbake|cc1plus' | cut -c1-80 | head -3
echo "--- leftover processes above (none expected)"
cd /home/alpha
setsid nohup bash /home/alpha/bb.sh wpewebkit > /home/alpha/wpe-build15.log 2>&1 < /dev/null &
sleep 45
tail -c 500 /home/alpha/wpe-build15.log | tr '\r' '\n' | tail -3
echo "compilers now: $(pgrep -c cc1plus)"
