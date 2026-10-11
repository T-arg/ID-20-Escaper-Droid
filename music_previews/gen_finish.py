#!/usr/bin/env python3
"""Three 'you finished the game' happy loops for Escaper Droid (ATMlib). Full title-song volume (PCT=100).
Trick: the 4-bar melody track ends with ATM_ADD_TRA(7); called twice (REPEAT 1) it plays once in the home key
and once a fifth higher; the next loop's SET_TRA resets the key, so no cleanup bytes are needed.
Harmony/bass call the SAME melody track with a different SET_TRA (octave shifts)."""
import sys, os, wave
from array import array
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_spy as g, atmsim
from gen_spy import *
g.PCT = 100
def N(*pairs): return [c for nm, d in pairs for c in n_(nm, d)]

def mk(var, title, tempo, L, lead, lead_vol, harm_vol, harm_tra, bass, drum, extra):
    s = Song(var, title, tempo, L)
    s.track('lead', [SETTRA(0), VOL(lead_vol), REPEAT(1, 'lcyc'), GOTO('lead')])
    s.track('harm', [SETTRA(harm_tra), VOL(harm_vol), REPEAT(1, 'lcyc'), GOTO('harm')])
    s.track('bass', bass[0]); s.track('drum', drum)
    s.track('lcyc', lead + [ADDTRA(7), RET()])
    for name, cmds in extra: s.track(name, cmds)
    s.entry = {0: 'lead', 1: 'harm', 2: 'bass', 3: 'drum'}
    return s

# F1 Hop Hop Hooray - C major, 4/4, bass = same melody 2 octaves down
m1 = N(('C5',8),('E5',8),('G5',16),('A5',8),('G5',8),('E5',16),
       ('F5',8),('A5',8),('C6',16),('A5',8),('G5',8),('F5',16),
       ('E5',8),('G5',8),('E5',8),('C5',8),('D5',16),('E5',16),
       ('D5',8),('E5',8),('D5',8),('B4',8),('C5',32))
F1 = mk('finishHop', 'Hop Hop Hooray', 36, 512, m1, 63, 30, -12,
        ([SETTRA(-24), VOL(45), REPEAT(1, 'lcyc'), GOTO('bass')],),
        [VOL(48), SLV(12), DELAY(8), VOL(14), SLV(7), DELAY(8), GOTO('drum')], [])

# F2 Marching Home - G major dotted march, own oom-pah bass cycle
m2 = N(('G4',12),('A4',4),('B4',12),('D5',4),('G5',16),('E5',12),('D5',4),
       ('C5',12),('D5',4),('E5',12),('G5',4),('A5',12),('G5',4),('E5',16),
       ('D5',12),('E5',4),('F#5',12),('A5',4),('G5',12),('F#5',4),('D5',16),
       ('E5',12),('D5',4),('C5',12),('E5',4),('D5',16),('B4',8),('A4',8))
F2 = mk('finishMarch', 'Marching Home', 32, 512, m2, 63, 30, -12,
        ([SETTRA(0), VOL(45), REPEAT(1, 'bcyc'), GOTO('bass')],),
        [VOL(48), SLV(12), DELAY(16), VOL(30), SLV(5), DELAY(16), GOTO('drum')],
        [('bcyc', [REPEAT(1,'pair'), ADDTRA(5), REPEAT(1,'pair'), ADDTRA(2), REPEAT(1,'pair'), ADDTRA(-7), REPEAT(1,'pair'), ADDTRA(7), RET()]),
         ('pair', N(('G2',16),('D3',16)) + [RET()])])

# F3 Skipping Waltz - F major 3/4 (36-tick bars), own bass cycle
m3 = N(('F4',6),('A4',6),('C5',12),('A4',6),('C5',6),
       ('D5',6),('F5',6),('A5',12),('F5',6),('D5',6),
       ('C5',6),('E5',6),('G5',12),('E5',6),('C5',6),
       ('D5',12),('C5',12),('A4',12))
F3 = mk('finishWaltz', 'Skipping Waltz', 28, 288, m3, 63, 30, -12,
        ([SETTRA(0), VOL(45), REPEAT(1, 'bcyc'), GOTO('bass')],),
        [VOL(48), SLV(12), DELAY(12), REPEAT(1, 'tick'), GOTO('drum')],
        [('bcyc', [REPEAT(0,'wbar'), ADDTRA(-3), REPEAT(0,'wbar'), ADDTRA(-2), REPEAT(0,'wbar'), ADDTRA(5), REPEAT(0,'wbar'), ADDTRA(7), RET()]),
         ('wbar', N(('F2',12),('C3',24)) + [RET()]),
         ('tick', [VOL(14), SLV(7), DELAY(12), RET()])])

SONGS = [(F1,2,'finish1_Hop_Hop_Hooray'), (F2,2,'finish2_Marching_Home'), (F3,3,'finish3_Skipping_Waltz')]
SR = 16000
def render(s, loops):
    song = s.assemble()[0]; atmsim.simulate(song, s.L * loops)
    tl = atmsim.TIMELINE[:s.L * loops]; spt = SR / s.tempo
    out = array('h'); ph = [0.0]*4; lfsr = 1
    for t, row in enumerate(tl):
        n0 = int(round(t*spt)); n1 = int(round((t+1)*spt))
        for i in range(n1-n0):
            mix = 0.0
            for c in range(4):
                v, f = row[c]
                if v <= 0: continue
                a = min(v,63)/63.0
                if c == 3:
                    if i % 2 == 0: lfsr = (lfsr >> 1) ^ (0xB400 if lfsr & 1 else 0)
                    mix += a*0.5*(1 if lfsr & 1 else -1); continue
                ph[c] = (ph[c] + f*0.485/SR) % 1.0
                w = (1 if ph[c] < (0.25 if c == 0 else 0.5) else -1) if c < 2 else 2*ph[c]-1
                mix += a*w
            out.append(int(max(-1, min(1, mix/2.6))*22000))
    return out
if __name__ == '__main__':
    hdr = []
    for s, loops, fn in SONGS:
        ok, song = verify(s, quiet=True)
        txt, _ = s.render(f'{s.title} - finishing tune, {s.L} ticks/loop, tempo {s.tempo}')
        hdr.append(txt)
        d = render(s, loops)
        w = wave.open(fn + '.wav', 'wb'); w.setnchannels(1); w.setsampwidth(2); w.setframerate(SR); w.writeframes(d.tobytes()); w.close()
        print(fn, round(len(d)/SR,1), 's', len(song), 'bytes')
    open('finish_candidates.h', 'w').write('\n'.join(hdr))
