#!/usr/bin/env python3
"""Four spy / espionage in-game loops for Escaper Droid (ATMlib), 60 % music volume via MV()/MS().
Each song: 8 bars x 64 ticks = 512 ticks, self-looping on every channel (no STOP, no GOTO_ADV).
Tempo is set by the sketch (songTempo[]), not in the songs."""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import atmsim
from atmsim import simulate, note_name

PCT = 60
def MVv(v): return v * PCT // 100
def MSv(n): return max(1, (n * PCT + 50) // 100)

_NAMES = ['C', 'C_', 'D', 'D_', 'E', 'F', 'F_', 'G', 'G_', 'A', 'A_', 'B']
_PC = {'C': 0, 'C#': 1, 'D': 2, 'D#': 3, 'E': 4, 'F': 5, 'F#': 6, 'G': 7, 'G#': 8, 'A': 9, 'A#': 10, 'B': 11}

def nnum(name):
    pc, o = (name[:2], int(name[2:])) if name[1] == '#' else (name[0], int(name[1:]))
    return (o - 2) * 12 + _PC[pc] + 1

def NOTE(name):
    n = nnum(name); assert 1 <= n <= 63, name
    o = 2 + (n - 1) // 12; pc = _NAMES[(n - 1) % 12]
    return (f'ATM_NOTE_{pc[0]}{o}{"_" if len(pc) > 1 else ""}', [n])

def DELAY(d):
    assert 1 <= d <= 64, d
    return (f'ATM_DELAY({d})', [0x9F + d])

def _s(v): return f'(uint8_t){v}' if v < 0 else str(v)
def VOL(v):       return (f'ATM_VOL(MV({v}))', [0x40, MVv(v)])
def SLV(n):       return (f'ATM_SL_VOL(MS({n}))', [0x41, (-MSv(n)) & 0xFF])     # n = positive fade step (full-volume value)
def ARP(a, t):    return (f'ATM_ARP(0x{a:02X}, 0x{t:02X})', [0x47, a, t])
def ADDTRA(v):    return (f'ATM_ADD_TRA({_s(v)})', [0x4B, v & 0xFF])
def SETTRA(v):    return (f'ATM_SET_TRA({_s(v)})', [0x4C, v & 0xFF])
def VIB(d, r):    return (f'ATM_VIB({d}, {r})', [0x50, d, r])
def RET():        return ('ATM_RETURN', [0xFE])
def GOTO(t):      return ('GOTO', t)
def REPEAT(r, t): return ('REPEAT', r, t)
def n_(name, d):  return [NOTE(name), DELAY(d)]

class Song:
    def __init__(self, var, title, tempo, L=512):
        self.var, self.title, self.tempo, self.L = var, title, tempo, L
        self.TR, self.ORDER, self.entry = {}, [], {}
    def track(self, name, cmds):
        self.TR[name] = cmds; self.ORDER.append(name)
    def assemble(self):
        idx = {n: i for i, n in enumerate(self.ORDER)}
        blobs = []
        for name in self.ORDER:
            b = []
            for c in self.TR[name]:
                if c[0] == 'GOTO': b += [0xFC, idx[c[1]]]
                elif c[0] == 'REPEAT': b += [0xFD, c[1], idx[c[2]]]
                else: b += c[1]
            blobs.append(b)
        offs, pos = [], 0
        for b in blobs: offs.append(pos); pos += len(b)
        song = [len(self.ORDER)]
        for o in offs: song += [o & 0xFF, o >> 8]
        song += [idx[self.entry[k]] for k in range(4)]
        for b in blobs: song += b
        return song, idx, offs, blobs
    def render(self, comment):
        song, idx, offs, blobs = self.assemble()
        L = [f'// {comment}']
        L += [f'Song {self.var}[] = {{     // total song bytes = {len(song)}',
              f'  0x{len(self.ORDER):02X},                       // Number of tracks']
        for i, name in enumerate(self.ORDER):
            o = offs[i]
            L.append(f'  0x{o & 0xFF:02X}, 0x{o >> 8:02X},                 // Address of track {i:<2d} {o:5d}   {name}')
        L.append('')
        for k in range(4):
            e = self.entry[k]
            L.append(f'  0x{idx[e]:02X},                         // CH{k} entry -> track {idx[e]} ({e})')
        L.append('')
        for i, name in enumerate(self.ORDER):
            L.append(f'  //"Track {i}" {name}  [{len(blobs[i])}b]')
            for c in self.TR[name]:
                if c[0] == 'GOTO': L.append(f'  ATM_GOTO({idx[c[1]]}),   // -> {c[1]}')
                elif c[0] == 'REPEAT': L.append(f'  ATM_REPEAT({c[1]}, {idx[c[2]]}),   // {c[1] + 1}x {c[2]}')
                else: L.append(f'  {c[0]},')
            L.append('')
        L += ['};', '']
        return '\n'.join(L), song

# ---- shared drum building blocks (noise channel: VOL + SL_VOL + DELAY) -------------------------
def drum_kick_hats(nhats):          # kick(4) + hats up to 16 ticks
    c = [VOL(48), SLV(12), DELAY(4), VOL(14), SLV(7), DELAY(4)]
    rest = 8
    if nhats == 1: c += [VOL(14), DELAY(8)]
    else: c += [VOL(14), DELAY(4), VOL(14), DELAY(4)]
    return c

# =====================================================================================
# 1  DOUBLE ZERO - Bond-style, E minor / minor-major 7 colour, tempo 36 (135 BPM)
# =====================================================================================
s1 = Song('spyDoubleZero', 'Double Zero', 36)
s1.track('drums', [REPEAT(13, 'half'), GOTO('beat_A'), GOTO('beat_B'), GOTO('beat_A'), GOTO('fill'), GOTO('drums')])
s1.track('half', [GOTO('beat_A'), GOTO('beat_B'), RET()])
s1.track('beat_A', drum_kick_hats(1) + [RET()])
s1.track('beat_B', [VOL(44), SLV(5), DELAY(8), VOL(26), SLV(3), DELAY(8), RET()])
s1.track('fill', [VOL(30), SLV(4), DELAY(4), VOL(38), DELAY(4), VOL(46), DELAY(4), VOL(54), DELAY(4), RET()])
s1.track('lead', [VOL(38), SLV(2), SETTRA(0), GOTO('r1'), GOTO('r2'),
                  ADDTRA(-4), GOTO('r1'), ADDTRA(-1), GOTO('r2'),
                  SETTRA(0), GOTO('r1'), GOTO('r2'),
                  SETTRA(5), GOTO('r1'), SETTRA(-5), GOTO('r2'), GOTO('lead')])
s1.track('r1', n_('E5', 12) + n_('D#5', 4) + n_('E5', 8) + n_('G5', 8) +
                n_('F#5', 8) + n_('E5', 8) + n_('D#5', 8) + n_('B4', 8) + [RET()])
s1.track('r2', n_('E5', 24) + n_('B4', 8) + n_('G4', 8) + n_('A4', 8) + n_('B4', 16) + [RET()])
s1.track('chords', [VOL(30), SLV(3), REPEAT(1, 'st_em'),
                    ] + n_('C4', 24) + n_('C4', 24) + n_('C4', 16) + [GOTO('st_b7'),     # C stab: ARP 0x38 (C Eb B) is still set by st_em
                    REPEAT(1, 'st_em')] + n_('A3', 24) + n_('A3', 24) + n_('A3', 16) + [GOTO('st_b7'), GOTO('chords')])
s1.track('st_em', [ARP(0x38, 0x20)] + n_('E4', 24) + n_('E4', 24) + n_('E4', 16) + [RET()])
s1.track('st_b7', [ARP(0x46, 0x20)] + n_('B3', 24) + n_('B3', 24) + n_('B3', 16) + [RET()])
s1.track('bass', [VOL(63), SLV(6), SETTRA(0), REPEAT(1, 'bar'), SETTRA(-4), GOTO('bar'), SETTRA(-5), GOTO('bar'),
                  SETTRA(0), REPEAT(1, 'bar'), SETTRA(-7), GOTO('bar'), SETTRA(-5), GOTO('bar'), GOTO('bass')])
s1.track('bar', [REPEAT(2, 'beat'), GOTO('beat4'), RET()])
s1.track('beat', n_('E3', 8) + n_('E3', 4) + n_('E4', 4) + [RET()])
s1.track('beat4', n_('E3', 8) + n_('E3', 4) + n_('B3', 4) + [RET()])
s1.entry = {0: 'lead', 1: 'chords', 2: 'bass', 3: 'drums'}

# =====================================================================================
# 2  SHADOW WALK - stealth, D minor, creeping plucks + leading tones, tempo 26 (97 BPM)
# =====================================================================================
s2 = Song('spyShadowWalk', 'Shadow Walk', 26)
s2.track('drums', [REPEAT(15, 'pair'), GOTO('drums')])
s2.track('pair', [VOL(14), SLV(8), DELAY(16), VOL(30), SLV(10), DELAY(16), RET()])
s2.track('lead', [VOL(38), SLV(3), SETTRA(0), GOTO('r1'), GOTO('r2'),
                  SETTRA(5), GOTO('r1'), SETTRA(7), GOTO('r2'),
                  SETTRA(0), GOTO('r1'), GOTO('r2'),
                  SETTRA(-4), GOTO('r1'), SETTRA(7), GOTO('r2'), GOTO('lead')])
s2.track('r1', n_('D5', 16) + n_('F5', 8) + n_('E5', 8) + n_('C#5', 16) + n_('D5', 16) + [RET()])
s2.track('r2', n_('A4', 24) + n_('A#4', 8) + n_('A4', 16) + n_('G4', 16) + [RET()])
s2.track('chords', [VOL(26), SLV(1), ARP(0x34, 0x23)] + n_('D4', 64) + n_('D4', 64) + n_('G3', 64) +
                   [ARP(0x46, 0x23)] + n_('A3', 64) +
                   [ARP(0x34, 0x23)] + n_('D4', 64) + n_('D4', 64) +
                   [ARP(0x43, 0x23)] + n_('A#3', 64) +
                   [ARP(0x46, 0x23)] + n_('A3', 64) + [GOTO('chords')])
s2.track('bass', [VOL(63), SLV(10), SETTRA(0), REPEAT(1, 'bar'), SETTRA(5), GOTO('bar'), SETTRA(7), GOTO('bar'),
                  SETTRA(0), REPEAT(1, 'bar'), SETTRA(-4), GOTO('bar'), SETTRA(7), GOTO('bar'), GOTO('bass')])
s2.track('bar', n_('D3', 16) + n_('D3', 8) + n_('D3', 8) + n_('A3', 16) + n_('D3', 16) + [RET()])
s2.entry = {0: 'lead', 1: 'chords', 2: 'bass', 3: 'drums'}

# =====================================================================================
# 3  CHASE SEQUENCE - Gm, chugging square, syncopated saw, 16th riff, tempo 40 (150 BPM)
# =====================================================================================
s3 = Song('spyChase', 'Chase Sequence', 40)
s3.track('drums', [REPEAT(13, 'half'), GOTO('beat_A'), GOTO('beat_B'), GOTO('beat_A'), GOTO('fill'), GOTO('drums')])
s3.track('half', [GOTO('beat_A'), GOTO('beat_B'), RET()])
s3.track('beat_A', drum_kick_hats(2) + [RET()])
s3.track('beat_B', [VOL(44), SLV(5), DELAY(8), VOL(14), SLV(7), DELAY(4), VOL(14), DELAY(4), RET()])
s3.track('fill', [VOL(30), SLV(4), DELAY(4), VOL(38), DELAY(4), VOL(46), DELAY(4), VOL(54), DELAY(4), RET()])
s3.track('lead', [VOL(38), SLV(2), SETTRA(0), REPEAT(1, 'riff'), SETTRA(5), GOTO('riff'), SETTRA(7), GOTO('riff'),
                  SETTRA(0), REPEAT(1, 'riff'), SETTRA(5), GOTO('riff'), SETTRA(7), GOTO('riff'), GOTO('lead')])
s3.track('riff', n_('G4', 8) + n_('D5', 8) + n_('G5', 8) + n_('F5', 8) +
                 n_('D5', 12) + n_('C5', 4) + n_('D5', 8) + n_('G4', 8) + [RET()])
s3.track('chug', [VOL(26), SLV(3), SETTRA(0), REPEAT(15, 'chug1'), SETTRA(5), REPEAT(7, 'chug1'), SETTRA(7), REPEAT(7, 'chug1'),
                  SETTRA(0), REPEAT(15, 'chug1'), SETTRA(5), REPEAT(7, 'chug1'), SETTRA(7), REPEAT(7, 'chug1'), GOTO('chug')])
s3.track('chug1', n_('D4', 8) + [RET()])
s3.track('bass', [VOL(63), SLV(4), SETTRA(0), REPEAT(1, 'bar'), SETTRA(5), GOTO('bar'), SETTRA(7), GOTO('bar'),
                  SETTRA(0), REPEAT(1, 'bar'), SETTRA(5), GOTO('bar'), SETTRA(7), GOTO('bar'), GOTO('bass')])
s3.track('bar', [REPEAT(2, 'beat'), GOTO('beat4'), RET()])
s3.track('beat', n_('G2', 12) + n_('G2', 4) + [RET()])
s3.track('beat4', n_('G2', 8) + n_('D3', 8) + [RET()])
s3.entry = {0: 'lead', 1: 'chug', 2: 'bass', 3: 'drums'}

# =====================================================================================
# 4  THE VAULT - suspense, B minor, heartbeat bass, bells, F#7 tension + dim bar, tempo 24 (90 BPM)
# =====================================================================================
s4 = Song('spyVault', 'The Vault', 24)
s4.track('drums', [REPEAT(7, 'dbar'), GOTO('drums')])
s4.track('dbar', [VOL(36), SLV(9), DELAY(16), VOL(14), SLV(8), DELAY(8), VOL(14), DELAY(8),
                  VOL(36), SLV(9), DELAY(16), VOL(14), SLV(8), DELAY(16), RET()])
s4.track('lead', [VOL(38), SLV(2), VIB(2, 3), SETTRA(0), GOTO('r1'), DELAY(64),
                  SETTRA(-4), GOTO('r1'), SETTRA(-5), GOTO('r1'),
                  SETTRA(0), GOTO('r1')] + n_('F5', 16) + n_('D5', 16) + n_('B4', 32) +
                 [SETTRA(5), GOTO('r1'), SETTRA(-5), GOTO('r1'), GOTO('lead')])
s4.track('r1', n_('F#5', 32) + n_('B5', 16) + n_('A5', 16) + [RET()])
s4.track('chords', [VOL(26), SLV(1), ARP(0x34, 0x23)] + n_('B3', 64) + n_('B3', 64) +
                   [ARP(0x43, 0x23)] + n_('G3', 64) +
                   [ARP(0x46, 0x23)] + n_('F#3', 64) +
                   [ARP(0x34, 0x23)] + n_('B3', 64) +
                   [ARP(0x33, 0x23)] + n_('B3', 64) +
                   [ARP(0x34, 0x23)] + n_('E4', 64) +
                   [ARP(0x46, 0x23)] + n_('F#3', 64) + [GOTO('chords')])
s4.track('bass', [VOL(63), SLV(10), SETTRA(0), REPEAT(7, 'beat'), SETTRA(-4), REPEAT(3, 'beat'), SETTRA(-5), REPEAT(3, 'beat'),
                  SETTRA(0), REPEAT(7, 'beat'), SETTRA(5), REPEAT(3, 'beat'), SETTRA(-5), REPEAT(3, 'beat'), GOTO('bass')])
s4.track('beat', n_('B2', 4) + n_('B2', 4) + [DELAY(8), RET()])
s4.entry = {0: 'lead', 1: 'chords', 2: 'bass', 3: 'drums'}

SONGS = [s1, s2, s3, s4]

def verify(s, quiet=False):
    song, idx, offs, blobs = s.assemble()
    L = s.L
    ev, restarts, stops, maxstack, tempo = simulate(song, L * 3 + 40)
    tl = [list(t) for t in atmsim.TIMELINE]
    ok = True
    if restarts: print('FAIL restarts', restarts); ok = False
    if [x for x in stops if x[0] > 0]: print('FAIL channel stopped', stops[:4]); ok = False
    nz = lambda r: [(v, f if v else 0) for v, f in r]
    for t in range(L, 3 * L):
        if nz(tl[t]) != nz(tl[t - L]):
            print(f'FAIL {s.title}: tick {t} differs from tick {t - L}', nz(tl[t]), nz(tl[t - L])); ok = False; break
    if maxstack > 7: print('FAIL depth', maxstack); ok = False
    def loop_events(k): return [(t - L * k,) + e[1:] for e in ev for t in [e[0]] if L * k <= t < L * (k + 1)]
    if not (loop_events(0) == loop_events(1) == loop_events(2)):
        print('FAIL loops differ'); ok = False
    for e in ev:        # note + transposition in range
        if e[2] == 'note' and not (e[3] == 0 or 1 <= e[3] <= 63): print('FAIL note range', e); ok = False
    # each track called from track 0?  (never call track 0)
    for name in s.ORDER:
        for c in s.TR[name]:
            if c[0] in ('GOTO', 'REPEAT') and idx[c[-1]] == 0 and name != s.ORDER[0]:
                print('FAIL: track 0 called from', name); ok = False
    for n in range(4):   # entry self-loop
        e = s.entry[n]
        if s.TR[e][-1] != ('GOTO', e): print('FAIL entry not self-looping', e); ok = False
    print(f'{s.title:16s} tracks={len(s.ORDER):2d} bytes={len(song):3d} depth={maxstack} ticks/loop={L} tempo={s.tempo} -> {"OK" if ok else "PROBLEMS"}')
    if not quiet:
        names = ['CH0 lead ', 'CH1 chord', 'CH2 bass ']
        l0 = [(t,) + e[1:] for e in ev for t in [e[0]] if t < L]
        for n in range(3):
            print('  ' + names[n])
            for bar in range(8):
                row = [note_name(e[3]) + f'@{e[0] % 64:02d}' for e in l0 if e[1] == n and e[2] == 'note' and e[0] // 64 == bar]
                print(f'    bar {bar + 1}: ' + ' '.join(row))
    return ok, song

if __name__ == '__main__':
    allok = True
    for s in SONGS:
        ok, song = verify(s, quiet=('-q' in sys.argv))
        allok &= ok
    print('ALL OK' if allok else 'SOME PROBLEMS')
