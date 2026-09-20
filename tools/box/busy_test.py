import os, subprocess, time
DECODER_DEVICES = ("/dev/dvb/adapter0/video0", "/dev/dvb/adapter0/audio0")
def decoderBusy():
	me = str(os.getpid())
	try: pids = [n for n in os.listdir("/proc") if n.isdigit() and n != me]
	except OSError: return False
	for pid in pids:
		try:
			for fd in os.listdir("/proc/%s/fd" % pid):
				try:
					if os.readlink("/proc/%s/fd/%s" % (pid, fd)) in DECODER_DEVICES: return True
				except OSError: pass
		except OSError: continue
	return False
t = time.time(); print("busy now (enigma2 holds video0 while it plays):", decoderBusy(), "in %.0f ms" % ((time.time() - t) * 1000))
