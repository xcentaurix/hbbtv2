# -*- coding: utf-8 -*-
# WPE HbbTV test plugin (HbbTV 2.0 experiment)
#
# Shows a WPE WebKit page on top of enigma2 (via the external wpe_fb process) and gives it the remote control:
#
#   - a full-screen, borderless, transparent Screen is opened. As the top screen it is the only one whose
#     actions run, so the remote keys go to it and not to the infobar / channel list underneath;
#   - every key is forwarded to wpe_fb through a FIFO (/tmp/wpe_fb.ctl) as "key <name>" and arrives in the page as
#     a normal DOM keydown event;
#   - EXIT closes the app: "quit" is sent, wpe_fb releases the screen, then enigma2 is told to repaint everything
#     (getDesktop(0).paint()) so nothing of the overlay is left behind.
#
# wpe_fb itself keeps the overlay on top of enigma2's redraws (page flips) - see wpe_fb.c "guard" mode.
#
# Files it expects next to this plugin (installed with it):
#   run_wpe.sh   starts wpe_fb with the right environment
#   pages/*.html the pages offered in the chooser
import os

from enigma import eConsoleAppContainer, eTimer, getDesktop, iServiceInformation
from Components.ActionMap import ActionMap
from Plugins.Plugin import PluginDescriptor
from Screens.ChoiceBox import ChoiceBox
from Screens.MessageBox import MessageBox
from Screens.Screen import Screen

BASE = os.path.dirname(os.path.abspath(__file__))
RUN = f"{BASE}/run_wpe.sh"
PAGES = f"{BASE}/pages"
CTL = "/tmp/wpe_fb.ctl"
EVT = "/tmp/wpe_fb.evt"
LOG = "/tmp/wpe_fb.log"

# Keys forwarded to the page; the names match the "mapto" values in keymap.xml and wpe_fb's key table.
FORWARDED_KEYS = ["up", "down", "left", "right", "ok", "back", "menu", "red", "green", "yellow", "blue",
	"play", "pause", "stop", "ff", "rew", "rec"] + [str(n) for n in range(10)]


PLANE = "/proc/stb/vmpeg/0/dst_%s"
PLANE_NAMES = ("left", "top", "width", "height")
PLANE_BOUNCE = ("00000010", "00000010", "000002b0", "00000220")  # any window that differs from full screen


def readPlane():
	try:
		return [open(PLANE % name).read().strip() for name in PLANE_NAMES]
	except OSError:
		return None


DECODER_DEVICES = ("/dev/dvb/adapter0/video0", "/dev/dvb/adapter0/audio0")


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


PLANE_FULL = ("00000000", "00000000", "000002d0", "00000240")  # the whole output: enigma2's own full-screen window


def sanePlane(values):
	"""The video window to go back to. Whatever the window is when the decoder is taken over is not to be trusted: it may be
	that of a mini-TV in an enigma2 menu (the Extensions menu this plugin is started from has one), and restoring that leaves the
	live picture in a corner - for good, since the next session would remember it again. A window that is not (nearly) the
	whole output is replaced by the full-screen one."""
	try:
		if values and int(values[2], 16) >= 0x2b0 and int(values[3], 16) >= 0x220:
			return values
	except ValueError:
		pass
	return list(PLANE_FULL)


def writePlane(values):
	try:
		for name, value in zip(PLANE_NAMES, values):
			open(PLANE % name, "w").write(value + "\n")
		open(PLANE % "apply", "w").write("1\n")
	except OSError:
		pass


class VideoHandover:
	"""Hardware video (dvbvideosink/dvbaudiosink in the browser) needs the video and audio decoder, which enigma2 holds for
	the live service (/dev/dvb/adapter0/video0 and audio0, and the sinks open exactly those): stop the service first, and
	afterwards play it again. The driver of the dm9xx ignores a plain full-screen window while the decoder was not running
	(see eVideoWidget::updatePosition), so after the service is back the window is "bounced": first a different one, then the
	remembered one."""

	def __init__(self, session):
		self.session = session
		self.ref = None
		self.plane = None
		self.active = False
		self.step = 0
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
		nav = self.session.nav
		self.ref = nav.getCurrentlyPlayingServiceOrGroup() or nav.getCurrentlyPlayingServiceReference()
		self.plane = sanePlane(readPlane())
		nav.stopService()
		self.active = True

	def release(self):
		if not self.active:
			return
		self.active = False
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

	def bounce(self):
		if not self.plane:
			return
		if self.step == 0:
			self.step = 1
			writePlane(PLANE_BOUNCE)
			self.timer.start(1000, True)
		else:
			writePlane(self.plane)


handovers = []  # a handover has to outlive its screen: its timer finishes the job after the screen is gone


class WPEScreen(Screen):
	# skin is set in main() from the real desktop size (same pattern as DVDOverlay)
	skin = """<screen name="WPEScreen" position="0,0" size="1920,1080" flags="wfNoBorder" backgroundColor="transparent" />"""

	def __init__(self, session, page, hwvideo=False):
		Screen.__init__(self, session)
		self.page = page
		self.hwvideo = hwvideo
		self.handover = None
		self.closing = False
		self.finished = False

		actions = {name: (lambda name=name: self.sendKey(name)) for name in FORWARDED_KEYS}
		actions["exit"] = self.stop
		self["actions"] = ActionMap(["WPEHbbTVActions"], actions, -1)

		self.killTimer = eTimer()
		self.killTimer.callback.append(self.forceKill)

		# events from wpe_fb (see "decoder handover" there): it writes "acquire" when media needs the decoder and "release" when
		# it is done with it; polled, an enigma2 timer being the simplest way to watch a FIFO
		self.evtFd = None
		self.evtBuf = b""
		self.evtTimer = eTimer()
		self.evtTimer.callback.append(self.pollEvents)
		self.freeTimer = eTimer()
		self.freeTimer.callback.append(self.decoderFree)

		self.container = eConsoleAppContainer()
		self.container.appClosed.append(self.appClosed)

		self.onLayoutFinish.append(self.start)
		self.onClose.append(self.cleanup)

	# --- process ---------------------------------------------------------------------------------------------

	def start(self):
		if not os.path.exists(RUN):
			self.session.open(MessageBox, f"{RUN} not found", MessageBox.TYPE_ERROR)
			self.finish()
			return
		env = ""
		if self.hwvideo:
			# Hardware video, but the live service keeps playing (an application runs on top of the live picture) until media
			# really needs the decoder: wpe_fb then sends "acquire" (pollEvents), and "release" when it is done with it.
			self.handover = VideoHandover(self.session)
			handovers.append(self.handover)
			try:
				os.unlink(EVT)  # a stale FIFO of an earlier run: wpe_fb creates a fresh one
			except OSError:
				pass
			self.evtTimer.start(100, False)
			env = "WPE_HWVIDEO=1 "
		if self.container.execute(f'{env}{RUN} "{self.page}" > {LOG} 2>&1') != 0:
			self.session.open(MessageBox, "could not start wpe_fb", MessageBox.TYPE_ERROR)
			self.finish()

	def appClosed(self, retval):
		# either we asked it to quit, or it ended by itself (crash, page load error, ...)
		self.killTimer.stop()
		self.finish()

	def forceKill(self):
		if self.container.running():
			self.container.kill()

	# --- control channel -------------------------------------------------------------------------------------

	def send(self, line):
		try:
			fd = os.open(CTL, os.O_WRONLY | os.O_NONBLOCK)  # fails while wpe_fb is not (yet) reading
		except OSError:
			return False
		try:
			os.write(fd, (line + "\n").encode())
		except OSError:
			return False
		finally:
			os.close(fd)
		return True

	def sendKey(self, name):
		if not self.closing:
			self.send(f"key {name}")

	# --- decoder handover --------------------------------------------------------------------------------------

	def pollEvents(self):
		if self.evtFd is None:
			try:
				self.evtFd = os.open(EVT, os.O_RDONLY | os.O_NONBLOCK)
			except OSError:
				return  # wpe_fb has not created it yet
		try:
			data = os.read(self.evtFd, 4096)
		except BlockingIOError:
			return
		except OSError:
			data = b""
		if not data:  # the writer has gone
			os.close(self.evtFd)
			self.evtFd = None
			return
		lines = (self.evtBuf + data).split(b"\n")
		self.evtBuf = lines.pop()  # an incomplete last line waits for the rest
		for line in lines:
			event = line.strip().decode(errors="replace")
			if event == "acquire" and self.handover and not self.finished:
				self.handover.acquire()
				self.freeTimer.start(1200, True)  # give enigma2 a moment to close the decoder before wpe_fb hands it out
			elif event == "release" and self.handover:
				self.freeTimer.stop()
				self.handover.release()

	def decoderFree(self):
		if self.handover and self.handover.active and not self.finished:
			self.send("decoder-free")

	def closeEvents(self):
		self.evtTimer.stop()
		self.freeTimer.stop()
		if self.evtFd is not None:
			os.close(self.evtFd)
			self.evtFd = None

	# --- leaving ---------------------------------------------------------------------------------------------

	def stop(self):
		if self.closing:
			return
		self.closing = True
		if self.container.running():
			self.send("quit")
			self.killTimer.start(3000, True)  # if it does not quit by itself within 3 s, kill it
		else:
			self.finish()

	def finish(self):
		if self.finished:
			return
		self.finished = True
		# wpe_fb has released the screen by now: have enigma2 redraw everything, then drop our transparent screen
		getDesktop(0).paint()
		self.closeEvents()
		if self.handover:
			self.handover.release()  # if media still had the decoder: the live service comes back, its window is fixed later
		self.close()

	def cleanup(self):
		self.closeEvents()
		self.killTimer.stop()
		if self.container.running():
			self.container.kill()


def pageChosen(session, choice):
	if choice:
		size = getDesktop(0).size()
		WPEScreen.skin = f"""<screen name="WPEScreen" position="0,0" size="{size.width()},{size.height()}" flags="wfNoBorder" backgroundColor="transparent" />"""
		# pages that play video on the hardware plane (hw_*.html) and real applications (URLs, which may play video whenever
		# they like) take the decoder from the live service; the other test pages leave the live picture alone
		page = choice[1]
		hwvideo = page.startswith(("http://", "https://")) or os.path.basename(page).startswith("hw_")
		session.open(WPEScreen, page, hwvideo)


def main(session, **kwargs):
	if not os.path.isdir(PAGES):
		session.open(MessageBox, f"{PAGES} not found", MessageBox.TYPE_ERROR)
		return
	pages = sorted(name for name in os.listdir(PAGES) if name.endswith(".html"))
	if not pages:
		session.open(MessageBox, f"No .html pages in {PAGES}", MessageBox.TYPE_ERROR)
		return
	choices = [(name[:-5], os.path.join(PAGES, name)) for name in pages]
	session.openWithCallback(lambda choice: pageChosen(session, choice), ChoiceBox, title="WPE HbbTV test page  (EXIT closes the page)", list=choices)


def currentServiceAppUrl(session):
	# enigma2 keeps the autostart application URL of the AIT of the current service (see eDVBServicePMTHandler::AITready)
	service = session.nav.getCurrentService()
	info = service and service.info()
	return (info and info.getInfoString(iServiceInformation.sHBBTVUrl)) or ""


def channelApp(session, **kwargs):
	url = currentServiceAppUrl(session)
	if not url.startswith(("http://", "https://")):
		session.open(MessageBox, "The current channel does not signal an HbbTV application (no AIT autostart URL).", MessageBox.TYPE_INFO, timeout=5)
		return
	pageChosen(session, (url, url))


def Plugins(**kwargs):
	return [PluginDescriptor(name="WPE HbbTV Test", description="WPE WebKit HbbTV 2.0 experiment: test pages on top of enigma2",
		where=PluginDescriptor.WHERE_EXTENSIONSMENU, fnc=main),
		PluginDescriptor(name="WPE HbbTV: channel app", description="Run the HbbTV application of the current channel (ORB engine, mock platform)",
		where=PluginDescriptor.WHERE_EXTENSIONSMENU, fnc=channelApp)]
