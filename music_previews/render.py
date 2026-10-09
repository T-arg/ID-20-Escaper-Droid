import wave, struct, random, sys
from array import array
import gen_spy as g, atmsim
SR = 16000
def render(s, loops=2):
    song = s.assemble()[0]
    simulate = atmsim.simulate
    simulate(song, s.L * loops)
    tl = atmsim.TIMELINE[:s.L * loops]
    spt = SR / s.tempo                      # samples per tick (ticks per second = tempo on hardware)
    out = array('h'); ph = [0.0] * 4; lfsr = 1; acc = 0.0
    for t, row in enumerate(tl):
        n0 = int(round(t * spt)); n1 = int(round((t + 1) * spt))
        for i in range(n1 - n0):
            mix = 0.0
            for c in range(4):
                v, f = row[c]
                if v <= 0: continue
                a = min(v, 63) / 63.0
                if c == 3:
                    if i % 2 == 0: lfsr = (lfsr >> 1) ^ (0xB400 if lfsr & 1 else 0)
                    mix += a * 0.5 * (1 if lfsr & 1 else -1)
                    continue
                fr = f * 0.485            # table frequency is halved on hardware
                ph[c] = (ph[c] + fr / SR) % 1.0
                if c == 0: w = 1 if ph[c] < 0.25 else -1
                elif c == 1: w = 1 if ph[c] < 0.5 else -1
                else: w = 2 * ph[c] - 1
                mix += a * w
            out.append(int(max(-1, min(1, mix / 2.6)) * 22000))
    return out
for k, s in enumerate(g.SONGS):
    data = render(s)
    fn = f'spy{k+1}_{s.title.replace(" ", "_")}.wav'
    w = wave.open(fn, 'wb'); w.setnchannels(1); w.setsampwidth(2); w.setframerate(SR); w.writeframes(data.tobytes()); w.close()
    print(fn, len(data) / SR, 's')
