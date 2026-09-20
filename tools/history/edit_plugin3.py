p = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/WPEHbbTV/plugin.py"
s = open(p).read()


def sub(old, new):
    global s
    assert s.count(old) == 1, (old[:70], s.count(old))
    s = s.replace(old, new)


# 1) who has the decoder open
sub('''PLANE_FULL = ("00000000", "00000000", "000002d0", "00000240")''',
    '''DECODER_DEVICES = ("/dev/dvb/adapter0/video0", "/dev/dvb/adapter0/audio0")


def decoderBusy():
	"""Does any process other than enigma2 have the video or audio decoder open? (enigma2 itself has neither while the service is
	stopped.) The browser's release event comes a moment before its web process has really let go of them, and a service that is
	started meanwhile is ignored by the driver ("VIDEO0: ignored request to start xpt ... its already running") and then killed
	when the last user closes the decoder: the live picture freezes on the last frame of the video."""
	me = str(os.getpid())
	try:
		pids = [name for name in os.listdir("/proc") if name.isdigit() and name != me]
	except OSError:
		return False
	for pid in pids:
		try:
			for fd in os.listdir("/proc/%s/fd" % pid):
				try:
					if os.readlink("/proc/%s/fd/%s" % (pid, fd)) in DECODER_DEVICES:
						return True
				except OSError:
					pass
		except OSError:
			continue
	return False


PLANE_FULL = ("00000000", "00000000", "000002d0", "00000240")''')

# 2) VideoHandover: wait for the decoder to be free before playing the service again
sub('''		self.step = 0
		self.timer = eTimer()
		self.timer.callback.append(self.bounce)

	def acquire(self):
		if self.active:
			return
		nav = self.session.nav''',
    '''		self.step = 0
		self.waited = 0
		self.timer = eTimer()
		self.timer.callback.append(self.bounce)
		self.playTimer = eTimer()
		self.playTimer.callback.append(self.playWhenFree)

	def acquire(self):
		if self.active:
			return
		if self.playTimer.isActive():
			# the service has not been played again yet (a new video started right away): it is still stopped, keep the
			# reference and the window that were remembered
			self.playTimer.stop()
			self.timer.stop()
			self.active = True
			return
		nav = self.session.nav''')
sub('''		self.active = False
		if self.ref:
			self.session.nav.playService(self.ref)
		self.step = 0
		self.timer.start(4000, True)  # the decoder has to be running again before the driver takes the new window
''',
    '''		self.active = False
		self.waited = 0
		self.playTimer.start(100, True)

	def playWhenFree(self):
		if decoderBusy() and self.waited < 6000:
			self.waited += 200
			self.playTimer.start(200, True)
			return
		if self.ref:
			self.session.nav.playService(self.ref)
		self.step = 0
		self.timer.start(4000, True)  # the decoder has to be running again before the driver takes the new window
''')
open(p, "w").write(s)
print("ok")
