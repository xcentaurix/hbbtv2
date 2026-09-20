#!/usr/bin/env python3
"""Protocol test of wpe_fb's decoder handover with a fake web process and a fake plugin (no decoder touched)."""
import glob, os, socket, subprocess, sys, time

os.chdir("/media/hdd/wpe-test")
env = dict(os.environ)
exec(open("env.sh").read().replace("export ", "").split("\n")[0]) if False else None
# reuse env.sh through a shell
sh_env = subprocess.run(["sh", "-c", ". ./env.sh; export WPE_FB_NO_BLANK=1; env"], capture_output=True, text=True).stdout
env = dict(l.split("=", 1) for l in sh_env.splitlines() if "=" in l)
for f in ("/tmp/t.evt", "/tmp/t.ctl"):
    try: os.unlink(f)
    except OSError: pass
log = open("/tmp/handover_test.log", "w")
p = subprocess.Popen(["./bin/wpe_fb", "--hwvideo-lazy", "--evt", "/tmp/t.evt", "--ctl", "/tmp/t.ctl", "--secs", "0", "pages/keys.html"], stdout=log, stderr=log, env=env)

def wait_for(pred, secs, what):
    t = time.time()
    while time.time() - t < secs:
        if pred(): return True
        time.sleep(0.05)
    print("TIMEOUT waiting for", what); return False

ok = True
ok &= wait_for(lambda: glob.glob("/tmp/wpe_dream.%d.sock" % p.pid) and os.path.exists("/tmp/t.evt") and os.path.exists("/tmp/t.ctl"), 15, "wpe_fb sockets")
sock_path = "/tmp/wpe_dream.%d.sock" % p.pid
evt = os.open("/tmp/t.evt", os.O_RDONLY | os.O_NONBLOCK)

def events():
    try: return os.read(evt, 4096).decode().split()
    except BlockingIOError: return []

def ctl(line):
    fd = os.open("/tmp/t.ctl", os.O_WRONLY | os.O_NONBLOCK); os.write(fd, (line + "\n").encode()); os.close(fd)

print("== 1. grant path")
c = socket.socket(socket.AF_UNIX); c.connect(sock_path); c.sendall(b"acquire 4242\n")
got = []
ok &= wait_for(lambda: got.extend(events()) or "acquire" in got, 3, "acquire event")
print("   event on the FIFO:", got)
ctl("decoder-free")
c.settimeout(3)
try: reply = c.recv(16)
except Exception as e: reply = repr(e).encode()
print("   web process gets:", reply)
ok &= reply.startswith(b"ok")

print("== 2. a second lease while the decoder is ours: immediate ok, no new event")
c2 = socket.socket(socket.AF_UNIX); c2.connect(sock_path); c2.sendall(b"acquire 4242\n"); c2.settimeout(2)
print("   second lease gets:", c2.recv(16), " new events:", events())

print("== 3. release only after the LAST lease closes")
c.close(); time.sleep(0.5); e1 = events(); print("   after first close, events:", e1); ok &= "release" not in e1
c2.close(); ok &= wait_for(lambda: "release" in got.__iadd__(events()), 3, "release event"); print("   after last close, events:", got)

print("== 4. denial when the plugin never answers (takes 9 s)")
c3 = socket.socket(socket.AF_UNIX); c3.connect(sock_path); c3.sendall(b"acquire 7\n"); c3.settimeout(12)
t = time.time()
try: reply = c3.recv(16)
except Exception as e: reply = repr(e).encode()
print("   web process gets:", reply, "after %.1f s; events:" % (time.time() - t), events())
ok &= reply.startswith(b"no")
c3.close()

ctl("quit"); time.sleep(1.5); p.poll()
print("RESULT:", "PASS" if ok else "FAIL")
print("leftovers:", glob.glob("/tmp/wpe_dream.*.sock"), os.path.exists("/tmp/t.evt"))
