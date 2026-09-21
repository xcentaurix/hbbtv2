import sys
sys.path.insert(0, '.')
import nav_analyze as A
GAP = 1_200_000   # frames closer than this belong to one cluster
print("%-6s %5s %7s %8s | %s" % ("run", "keys", "dropped", "steps", "cluster end after the LAST SEND (ms) | frames in cluster | Mpx in cluster | page still moving 1st cluster after first send"))
for l in sys.argv[1:]:
    run, r = A.analyse('nav_%s.log' % l)
    ph = r['phases']
    t0, t1 = ph['burst']
    keys = [ts for ts, k in run['keys_in'] if t0 <= ts < t1]
    snds = [up * 1e6 + run['offset'] for ts, k, up in run['sends'] if t0 <= ts < t1 and k == 'right']
    fr = [f for f in run['frames'] if f['ts'] >= snds[0]]
    # first cluster starting at the first send
    cl = []
    for f in fr:
        if not cl or f['ts'] - cl[-1]['ts'] <= GAP:
            cl.append(f)
        else:
            break
    last_send = snds[-1]
    tail = (cl[-1]['ts'] - last_send) / 1000 if cl else None
    print("%-6s %5d %7d %8s | %9.0f | %3d | %5.2f | %s" % (l, len(keys), r['burst']['dropped'], "", tail, len(cl), sum(f['px'] for f in cl) / 1e6, "first frame %+.0f ms after first send" % ((cl[0]['ts'] - snds[0]) / 1000)))
