import re, sys, types, py_compile, tempfile
# unit test of plugin.py readComponents() with stub enigma2 objects (no box needed): python3 test_components.py
P = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/WPEHbbTV/plugin.py"
py_compile.compile(P, cfile=tempfile.mktemp(), doraise=True); print("plugin.py compiles")
src = open(P).read()
assert "\n    " not in src.split("VIDEO_ENCODINGS")[1].split("PLANE =")[0], "spaces used for indentation"

class SI:  # iServiceInformation
    sVideoPID, sVideoType, sIsCrypted, sAspect = 1, 2, 3, 4

class Info:
    def __init__(s, v): s.v = v
    def getInfo(s, k): return s.v.get(k)
class Track:
    def __init__(s, pid, lang, desc, ch=2): s.pid, s.lang, s.desc, s.ch = pid, lang, desc, ch
    def getPID(s): return s.pid
    def getLanguage(s): return s.lang
    def getDescription(s): return s.desc
    def getChannels(s): return s.ch
class Audio:
    def __init__(s, tracks, cur): s.t, s.c = tracks, cur
    def getCurrentTrack(s): return s.c
    def getNumberOfTracks(s): return len(s.t)
    def getTrackInfo(s, n): return s.t[n]
class Sub:
    def __init__(s, l): s.l = l
    def getSubtitleList(s): return s.l
class Service:
    def __init__(s, info, audio, sub): s.i, s.a, s.s = info, audio, sub
    def info(s): return s.i
    def audioTracks(s): return s.a
    def subtitle(s): return s.s

ns = {"re": re, "iServiceInformation": SI}
start = src.index("VIDEO_ENCODINGS ="); end = src.index("PLANE = ")
exec(src[start:end], ns)
rc = ns["readComponents"]

svc = Service(Info({1: 5101, 2: 1, 3: 0, 4: 1}),
              Audio([Track(5102, "deu", "AC3", 6), Track(5103, "eng/ger", "HE-AAC"), Track(5104, "mis", "MPEG"), Track(5102, "dup", "AC3")], 1),
              Sub([(0, 5105, 1, 2, "deu"), (1, 5106, 100, 1, "eng"), (0, 5105, 1, 2, "dup")]))
text, audio, subs, cur = rc(svc)
print(text); print(audio, cur); print(list(subs))
assert text.split(";")[0] == "V:5101:H.264:0:1"
assert "A:5102:deu:AC3:6:0:0" in text and "A:5103:eng:HEAAC:2:1:0" in text and "A:5104:mis:MPEG1_L2:2:0:0" in text
assert "S:5105:deu:DVB:0:0" in text and "S:5106:eng:TELETEXT:0:0" in text
assert audio == {5102: 0, 5103: 1, 5104: 2} and cur == 5103 and set(subs) == {5105, 5106}
assert text.count("A:") == 3 and text.count("S:") == 2
# no video, no audio object, no subtitles, unknown things
t2 = rc(Service(Info({1: -1}), None, None)); print(t2); assert t2[0] == ""
t3 = rc(Service(Info({1: 6001, 2: 6, 3: 1, 4: None}), Audio([Track(1, "", "Dolby Digital Plus (E-AC3)")], 0), None)); print(t3[0])
assert t3[0] == "V:6001:H.265:1:1;A:1:und:E-AC3:2:1:0"
print("all ok")
