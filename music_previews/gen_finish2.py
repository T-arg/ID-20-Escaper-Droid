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


def RISE(n): return (f'ATM_SL_VOL({n})', [0x41, n])
def cyc(call, offs, lift):
    a = [offs[1]-offs[0], offs[2]-offs[1], offs[3]-offs[2], lift-offs[3]]
    out = []
    for x in a: out += [call, ADDTRA(x)]
    return out + [RET()]
def italo(var, title, tempo, riff, offs, lift, mode):
    s = Song(var, title, tempo, 512)
    s.track('lead', [SETTRA(0), VOL(38), SLV(2), REPEAT(1, 'cycL'), GOTO('lead')])
    s.track('riff', riff + [RET()])
    s.track('cycL', cyc(GOTO('riff'), offs, lift))
    if mode == 'arp':
        s.track('arp', [SETTRA(0), VOL(22), REPEAT(1, 'cycA'), GOTO('arp')])
        s.track('abeat', N(('C4',4),('G4',4),('C5',4),('G4',4)) + [RET()])
        s.track('cycA', cyc(REPEAT(3, 'abeat'), offs, lift))
    else:
        s.track('harm', [SETTRA(-12), VOL(20), SLV(1), REPEAT(1, 'cycL'), GOTO('harm')])
    s.track('bass', [SLV(5), SETTRA(0), REPEAT(1, 'cycB'), GOTO('bass')])
    s.track('beat', [VOL(0), DELAY(4), VOL(63)] + N(('C3',4),('C4',4),('C3',4)) + [RET()])
    s.track('cycB', cyc(REPEAT(3, 'beat'), offs, lift))
    kick = [VOL(28), SLV(14), DELAY(4), VOL(12), SLV(6), DELAY(4), VOL(26), SLV(3), DELAY(8)]
    snare = [VOL(40), SLV(5), DELAY(8), VOL(26), SLV(3), DELAY(8)]
    if mode == 'fill':
        s.track('drum', [REPEAT(14, 'pair'), GOTO('dA'), VOL(10), RISE(3), DELAY(16), GOTO('drum')])
        s.track('dA', kick + [RET()]); s.track('pair', [GOTO('dA')] + snare + [RET()])
    else:
        s.track('drum', kick + snare + [GOTO('drum')])
    s.entry = {0: 'lead', 1: 'arp' if mode == 'arp' else 'harm', 2: 'bass', 3: 'drum'}
    return s

rA = N(('G4',8),('C5',8),('E5',8),('G5',8),('E5',16),('D5',8),('C5',8))
rB = N(('C5',12),('E5',4),('G5',12),('E5',4),('D5',8),('E5',8),('A5',16))
rC = N(('C5',4),('G4',4),('E5',4),('G4',4),('E5',4),('G4',4),('G5',4),('G4',4),
       ('D5',4),('G4',4),('E5',4),('G4',4),('C5',16))
A = italo('finishDisco', 'Happy Disco', 34, rA, (0,5,7,0), 7, 'echo')
B = italo('finishNeon', 'Victory Night', 36, rB, (0,-5,-7,-5), 5, 'arp')
C = italo('finishGlitter', 'Glitter Finale', 35, rC, (0,5,7,5), 2, 'fill')
SONGS = [(A,2,'finish4_Happy_Disco'), (B,2,'finish5_Victory_Night'), (C,2,'finish6_Glitter_Finale')]
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
    open('finish_candidates2.h', 'w').write('\n'.join(hdr))
