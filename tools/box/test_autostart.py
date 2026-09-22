#!/usr/bin/env python3
"""Test of the plugin's automatic banner and red button logic with a stubbed enigma2: the whole plugin.py is imported, AutoStart is driven with a fake
session, a fake timer and the real captured AIT (testdata/ait_zdfhd.txt).   usage: python3 test_autostart.py   (no box needed)"""
import importlib.util, os, queue, re, sys, types

HERE = os.path.dirname(os.path.abspath(__file__))
P = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/WPEHbbTV/plugin.py"
if not os.path.exists(P):
    P = os.path.join(HERE, "../../meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/WPEHbbTV/plugin.py")
P = os.environ.get("PLUGIN_PY", P)  # another copy of plugin.py to test


# ---- stubs of what enigma2 provides ----
def module(name, **attrs):
    m = types.ModuleType(name)
    m.__dict__.update(attrs)
    sys.modules[name] = m
    return m


class Callbacks(list):
    pass


class FakeTimer:
    instances = []

    def __init__(self):
        self.callback = Callbacks()
        self.active = False
        self.interval = None
        FakeTimer.instances.append(self)

    def start(self, interval, single=False):
        self.active, self.interval = True, interval

    def stop(self):
        self.active = False

    def fire(self):
        self.active = False
        for cb in list(self.callback):
            cb()


class FakeDesktop:
    def size(self):
        return types.SimpleNamespace(width=lambda: 1920, height=lambda: 1080)

    def paint(self):
        pass


class FakeActionMap:
    handlers = []

    @classmethod
    def getInstance(cls):
        return cls()

    def bindAction(self, context, priority, fnc):
        FakeActionMap.handlers.append((context, priority, fnc))


class SI:
    sPMTPID, sLiveStreamDemuxId, sVideoPID, sAudioPID, sVideoType, sIsCrypted, sAspect, sHBBTVUrl = range(8)


class FakeContainer:
    commands = []

    def __init__(self):
        self.appClosed = Callbacks()
        self.busy = False

    def execute(self, command):
        FakeContainer.commands.append(command)
        if self.busy:
            return -1  # what enigma2 answers when it runs something already
        self.busy = True
        return 0

    def running(self):
        return self.busy

    def kill(self):
        self.busy = False


class StubScreen:
    def __init__(self, session):
        self.session, self.widgets, self.onLayoutFinish, self.onClose = session, {}, [], []

    def __setitem__(self, name, value):
        self.widgets[name] = value

    def __getitem__(self, name):
        return self.widgets[name]


class StubWidget:
    instance = None

    def hide(self):
        pass

    def show(self):
        pass


module("enigma", eActionMap=FakeActionMap, eConsoleAppContainer=FakeContainer, eTimer=FakeTimer, getDesktop=lambda n: FakeDesktop(),
       iPlayableService=types.SimpleNamespace(evStart=1, evEnd=2), iServiceInformation=SI, ePoint=lambda x, y: ("point", x, y),
       eSize=lambda w, h: ("size", w, h))
module("Components")
module("Components.ActionMap", ActionMap=lambda *args: object())
module("Components.Pixmap", Pixmap=StubWidget)
module("Components.Label", Label=lambda text="": StubWidget())
module("Plugins")
module("Plugins.Plugin", PluginDescriptor=types.SimpleNamespace(WHERE_EXTENSIONSMENU=1, WHERE_SESSIONSTART=2, __call__=None))
module("Screens")
module("Screens.ChoiceBox", ChoiceBox=object)
module("Screens.MessageBox", MessageBox=types.SimpleNamespace(TYPE_INFO=0, TYPE_ERROR=1, TYPE_YESNO=2))
module("Screens.Screen", Screen=StubScreen)
module("keyids", KEYIDS={"KEY_RED": 398, "KEY_GREEN": 399, "KEY_YELLOW": 400, "KEY_BLUE": 401, "KEY_UP": 103, "KEY_DOWN": 108, "KEY_LEFT": 105, "KEY_RIGHT": 106,
                         "KEY_OK": 352, "KEY_BACK": 158, "KEY_EXIT": 174, "KEY_PLAY": 207, "KEY_PAUSE": 119, "KEY_STOP": 128, "KEY_FASTFORWARD": 208, "KEY_REWIND": 168,
                         **{"KEY_%d" % n: 2 + n for n in range(10)}})

spec = importlib.util.spec_from_file_location("wpe_plugin", P)
plug = importlib.util.module_from_spec(spec)
spec.loader.exec_module(plug)
print("plugin.py imports with stubs")

failures = 0


def check(cond, text):
    global failures
    if not cond:
        failures += 1
        print("FAIL:", text)


# ---- claimedKeys ----
check(plug.claimedKeys(0x1) == {"red"}, "a banner asks for red only")
check(plug.claimedKeys(0x1 | 0x10) >= {"red", "up", "down", "left", "right", "ok", "back", "exit"}, "an interactive application gets navigation and exit")
check("exit" not in plug.claimedKeys(0x1 | 0x2 | 0x4 | 0x8), "exit stays enigma2's until the navigation keys are asked for")
check(plug.claimedKeys(0x100) == {str(n) for n in range(10)}, "numeric keys")
check(plug.claimedKeys(0) == set(), "nothing asked for, nothing taken")
check(plug.KEY_NAMES[398] == "red" and plug.KEY_NAMES[2] == "0" and plug.KEY_NAMES[11] == "9", "rc key names")

# ---- fake session, service and overlay ----
lines = [l.split() for l in open(os.path.join(HERE, "testdata/ait_zdfhd.txt")) if l.strip()]
pid, sid, section = int(lines[0][0]), int(lines[0][1]), bytes.fromhex(lines[0][2])
CHANNEL = (1, 1011, sid, "ZDF HD")


class FakeReader:
    def __init__(self):
        self.events = queue.Queue()
        self.stopped = False

    def stop(self):
        self.stopped = True


class FakeOverlay:
    def __init__(self, channel, ait):
        self.channel, self.ait, self.keyset = channel, ait, 0
        self.keys, self.started, self.stopped, self.alive = [], False, False, True
        self.onClose = []

    def start(self):
        self.started = True

    def show(self):
        self.shown = True

    def running(self):
        return self.alive

    def sendKey(self, name, repeat=False):
        self.keys.append((name, repeat))

    def stop(self):
        self.stopped = True


class FakeSession:
    def __init__(self):
        self.nav = types.SimpleNamespace(event=[])
        self.dialogs = []

    def instantiateDialog(self, screen, *args):
        self.dialogs.append(args)
        return FakeOverlay(args[2], args[3])


state = {"channel": CHANNEL, "settings": {"WPE_AUTOSTART": "1", "WPE_REDBUTTON": "1"}, "readers": []}
plug.currentChannel = lambda session: state["channel"]
plug.readSettings = lambda: state["settings"]


def fake_start_reader(session):
    reader = FakeReader()
    state["readers"].append(reader)
    return reader, state["channel"]


plug.startAitReader = fake_start_reader

session = FakeSession()
auto = plug.AutoStart(session)
timers = {"settle": auto.settleTimer, "ait": auto.aitTimer}
check(session.nav.event == [auto.navEvent], "the controller listens to service events")
check(FakeActionMap.handlers and FakeActionMap.handlers[-1][1] == -plug.maxsize - 1 and FakeActionMap.handlers[-1][2] == auto.keyEvent, "key hook bound with the highest priority")

# ---- a zap: nothing starts before the service has settled ----
auto.navEvent(plug.iPlayableService.evStart)
check(timers["settle"].active and timers["settle"].interval == plug.AutoStart.SETTLE and not state["readers"], "settling timer, nothing read yet")
timers["settle"].fire()
check(len(state["readers"]) == 1 and timers["ait"].active and auto.collection, "settled: the AIT is being read")
# the AIT arrives
state["readers"][0].events.put(("section", pid, section))
timers["ait"].fire()
check(session.dialogs and auto.overlay is not None and auto.overlay.started, "AUTOSTART application in the AIT: the overlay is started")
check(getattr(auto.overlay, "shown", False), "and shown: a dialog from instantiateDialog() is invisible until show()")
check(session.dialogs[0][0] == "ait:" and session.dialogs[0][4] is False and session.dialogs[0][5] is True and len(session.dialogs[0]) == 6, "overlay: page ait:, no red key press, overlay mode")
overlay = auto.overlay

# ---- keys ----
RED, UP, OK, EXIT, VOL = 398, 103, 352, 174, 115
check(auto.keyEvent(RED, 0) == 0, "no key set yet: red stays enigma2's")
overlay.keyset = 0x1
check(auto.keyEvent(RED, 0) == 1 and overlay.keys == [("red", False)], "the banner asks for red: red goes to it")
check(auto.keyEvent(RED, 1) == 1, "and so does its break")
check(auto.keyEvent(RED, 1) == 0, "a second break is not ours")
check(auto.keyEvent(UP, 0) == 0 and auto.keyEvent(UP, 1) == 0, "up is enigma2's")
check(auto.keyEvent(EXIT, 0) == 0, "exit is enigma2's while only the banner is there")
check(auto.keyEvent(VOL, 0) == 0, "an unknown key is enigma2's")
overlay.keyset = 0x1 | 0x10
check(auto.keyEvent(UP, 0) == 1 and auto.keyEvent(UP, 2) == 1, "navigation asked for: up and its repeat are taken")
check(overlay.keys[-2:] == [("up", False), ("up", True)], "repeat is forwarded for arrows")
check(auto.keyEvent(OK, 0) == 1 and auto.keyEvent(OK, 2) == 1 and overlay.keys[-1] == ("ok", False), "ok repeats are swallowed, not forwarded")
check(auto.keyEvent(EXIT, 0) == 1 and overlay.keys[-1] == ("exit", False), "exit is the application's once it is interactive")
overlay.alive = False
check(auto.keyEvent(RED, 0) == 0, "a dead overlay takes nothing")
overlay.alive = True

# ---- the decoder is taken by the application's media: the service stops, then comes back; the overlay must stay ----
state["channel"] = None
auto.navEvent(plug.iPlayableService.evStart)
timers["settle"].fire()
check(not overlay.stopped, "service stopped for the decoder: the application stays")
state["channel"] = CHANNEL
auto.navEvent(plug.iPlayableService.evStart)
timers["settle"].fire()
check(not overlay.stopped, "the same service again: the application stays")
# ---- zapping to another service ----
state["channel"] = (1, 1011, 11111, "ZDFinfo")
auto.navEvent(plug.iPlayableService.evStart)
timers["settle"].fire()
check(overlay.stopped, "another service: the application is stopped")
check(timers["settle"].active, "and the new service is looked at again when it has gone")
for callback in overlay.onClose:
    callback()
check(auto.overlay is None and not auto.consumed, "closed: the controller is free again")

# ---- switched off / not signalled ----
state["settings"] = {"WPE_AUTOSTART": "0", "WPE_REDBUTTON": "1"}
state["readers"].clear()
timers["settle"].fire()
check(not state["readers"], "autostart off: the AIT is not even read")
state["settings"]["WPE_AUTOSTART"] = "1"
timers["settle"].fire()
check(len(state["readers"]) == 1, "on again: read")
state["readers"][0].events.put(("none",))
timers["ait"].fire()
check(auto.overlay is None and state["readers"][0].stopped and auto.collection is None, "a service without AIT: no overlay, reader stopped")

# ---- red button hook ----
started = []
plug.channelApp = lambda session, redButton=False, **k: started.append(redButton)
hook = plug.RedButtonHook(session)
hook.activated()
check(started == [True], "red button: starts the channel application in red button mode")
state["settings"]["WPE_REDBUTTON"] = "0"
hook.activated()
check(started == [True], "red button switched off: nothing")

# ---- the real screen, started twice as a dialog is (by its creator, and when its layout is finished): one wpe_fb, no error ----
plug.RUN = os.path.abspath(__file__)  # anything that exists
opened = []
real = plug.WPEScreen(types.SimpleNamespace(open=lambda *a: opened.append(a)), "ait:", False, None, None, False, True)
real.start()
real.start()
check(len(FakeContainer.commands) == 1 and "WPE_OVERLAY=1" in FakeContainer.commands[0], "a second start is ignored (%s)" % FakeContainer.commands)
check(not opened, "and there is no error message (%s)" % opened)
# the way the automatic banner really starts: with hardware video (page "ait:" makes it so in pageChosen / ChannelAppLauncher) - the environment of
# run_wpe.sh must keep WPE_OVERLAY=1 next to WPE_HWVIDEO=1, or wpe_fb writes the whole frame into the framebuffer and wipes enigma2's own screen
FakeContainer.commands.clear()
plug.VideoHandover = lambda session: types.SimpleNamespace(acquire=lambda: None, release=lambda: None, active=False)
banner = plug.WPEScreen(types.SimpleNamespace(open=lambda *a: opened.append(a)), "ait:", True, None, None, False, True)
banner.start()
banner_command = FakeContainer.commands[0] if FakeContainer.commands else ""
check(len(FakeContainer.commands) == 1 and "WPE_OVERLAY=1" in FakeContainer.commands[0] and "WPE_HWVIDEO=1" in FakeContainer.commands[0],
      "the banner with hardware video keeps WPE_OVERLAY=1 (%s)" % FakeContainer.commands)
FakeContainer.commands.clear()
manual = plug.WPEScreen(types.SimpleNamespace(open=lambda *a: opened.append(a)), "ait:", True, None, None, False, False)
manual.start()
check(len(FakeContainer.commands) == 1 and "WPE_OVERLAY" not in FakeContainer.commands[0] and "WPE_HWVIDEO=1" in FakeContainer.commands[0],
      "a screen of its own is not an overlay (%s)" % FakeContainer.commands)

# ---- the picture of the banner: a Pixmap widget of the screen shows wpe_fb's PNG ----
class FakeWidget:
    def __init__(self):
        self.calls = []

    def __getattr__(self, name):
        return lambda *args: self.calls.append((name,) + args)


class FakeComponent:
    def __init__(self):
        self.instance = FakeWidget()


screen = plug.WPEScreen.__new__(plug.WPEScreen)
screen.widgets = {"overlay": FakeComponent()}
screen.instance = FakeWidget()  # the window of the screen itself
screen.overlaySeq = 0
screen.overlayShown, screen.overlayGeometry, screen.overlayFull = False, None, False
screen.modal = False
executed = []
screen.session = types.SimpleNamespace(execDialog=lambda dialog: executed.append(dialog))
calls = screen.widgets["overlay"].instance.calls
window = screen.instance.calls
screen.showOverlay("overlay 1 100 200 640 120 /tmp/wpe_overlay_1.png".split())
check(window == [("resize", ("size", 640, 120)), ("move", ("point", 100, 200))], "the window is as big as the picture and sits where it goes (%s)" % window)
check(calls == [("resize", ("size", 640, 120)), ("setPixmapFromFile", "/tmp/wpe_overlay_1.png"), ("show",)], "the picture: size, the file, shown (%s)" % calls)
calls.clear()
window.clear()
screen.showOverlay("overlay 1 0 0 10 10 /tmp/wpe_overlay_1.png".split())
check(not calls and not window, "an event that is not newer than the one shown is ignored")
# the same size and place again (an animation frame): only the picture is exchanged - every resize, move and show costs enigma2 surfaces and textures
screen.showOverlay("overlay 2 100 200 640 120 /tmp/wpe_overlay_2.png".split())
check(not window and calls == [("setPixmapFromFile", "/tmp/wpe_overlay_2.png")], "same size, same place: only the picture (%s %s)" % (window, calls))
calls.clear()
screen.showOverlay("overlay 3 110 200 640 120 /tmp/wpe_overlay_3.png".split())
check(window == [("move", ("point", 110, 200))] and calls == [("setPixmapFromFile", "/tmp/wpe_overlay_3.png")], "moved: only a move (%s %s)" % (window, calls))
calls.clear()
window.clear()
screen.showOverlay("overlay 4 0 0 0 0 -".split())
check(calls == [("hide",)] and window == [("resize", ("size", 1, 1))] and screen.overlaySeq == 4, "nothing visible: the widget is hidden, the window shrinks")
calls.clear()
window.clear()
screen.showOverlay("overlay 5 0 0 0 0 -".split())
check(not calls and not window, "still nothing visible: nothing to do")
screen.showOverlay("overlay x".split())
screen.showOverlay("overlay 6 1 2 3".split())
check(not calls and not window and screen.overlaySeq == 5, "a broken event does nothing")
# the application has grown too big for pictures: wpe_fb draws into the framebuffer now, the picture goes away and later events are ignored
screen.showOverlay("overlay 7 100 200 640 120 /tmp/wpe_overlay_7.png".split())
calls.clear()
window.clear()
screen.showOverlay("overlay fullscreen".split())
check(calls == [("hide",)] and window == [("resize", ("size", 1, 1))] and screen.overlayFull, "fullscreen: the picture goes away (%s %s)" % (calls, window))
check(executed == [screen] and screen.modal and screen.isTmp, "fullscreen: the dialog becomes the executing screen (enigma2's infobar then stays away), closed for good by the session")
calls.clear()
window.clear()
screen.showOverlay("overlay 9 100 200 640 120 /tmp/wpe_overlay_9.png".split())
check(not calls and not window, "and no picture is shown after that")

# ---- the manual launcher on a session that keeps enigma2's rule: a modal cannot be opened while none is executing, and a closed one leaves only when the
# session has run its delay timer (StartEnigma.Session.open / close). The launcher closes its "Reading ..." box and then opens the next screen. ----
class ModalDialog:
    def __init__(self, session, screen, args, kwargs):
        self.session, self.screen, self.args, self.kwargs = session, screen, args, kwargs

    def close(self):
        self.session.close(self)


class ModalSession:
    def __init__(self):
        self.in_exec = True  # something (the extensions menu) is executing
        self.opened, self.pending = [], []

    def open(self, screen, *args, **kwargs):
        if not self.in_exec:
            raise RuntimeError("[StartEnigma] Error: Modal open are allowed only from a screen which is modal!")
        dialog = ModalDialog(self, screen, args, kwargs)
        self.opened.append(dialog)
        return dialog

    def openWithCallback(self, callback, screen, *args, **kwargs):
        return self.open(screen, *args, **kwargs)

    def close(self, dialog):
        self.in_exec = False  # execEnd: nothing executes until the delay timer has popped it
        self.pending.append(dialog)

    def runDelay(self):
        if self.pending:
            self.pending.clear()
            self.in_exec = True


modal = ModalSession()
state["settings"] = {"WPE_AUTOSTART": "0", "WPE_REDBUTTON": "1"}
state["channel"] = CHANNEL
state["readers"].clear()
launcher = plug.ChannelAppLauncher(modal)
launcher.start()
check(len(modal.opened) == 1, "the launcher shows its \"Reading ...\" box")
state["readers"][0].events.put(("section", pid, section))
launcher.timer.fire()
try:
    modal.runDelay()  # the session's delay timer, before the launcher's own timer for the next screen can fire
    launcher.afterBox.fire()
    check(len(modal.opened) == 2 and modal.opened[1].kwargs.get("title", "").startswith("HbbTV applications of"),
          "after the box is gone the launcher offers the applications of the channel (%d screens)" % len(modal.opened))
except RuntimeError as error:
    check(False, "the launcher opened a screen while none was executing: %s" % error)

# ---- leaving: an overlay that never became modal is deleted, one that did is closed as a screen ----
for modal in (False, True):
    leaving = plug.WPEScreen(types.SimpleNamespace(open=lambda *a: None, deleteDialog=lambda s: leave_calls.append("deleteDialog")), "ait:", False, None, None, False, True)
    leave_calls = []
    leaving.modal = modal
    leaving.close = lambda: leave_calls.append("close")
    leaving.finish()
    check(leave_calls == ["close" if modal else "deleteDialog"], "finish of an overlay (modal=%s): %s" % (modal, leave_calls))

# ---- wpe_fb ends when enigma2 is gone: the owner's pid goes to run_wpe.sh ----
check(re.search(r"WPE_OWNER=\d+ ", banner_command) is not None, "the environment names the owner process (%s)" % banner_command)

# ---- the settings menu offers both switches ----
keys = [k for k, *_ in plug.SETTINGS]
check("WPE_REDBUTTON" in keys and "WPE_AUTOSTART" in keys and "WPE_SIZE" not in keys, "settings: the two switches, no dead screen size entry")
print("all ok" if not failures else "FAILED (%d)" % failures)
sys.exit(1 if failures else 0)
