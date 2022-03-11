import("stdfaust.lib");

freq = hslider("freq",60,20,20000,0.01) : ba.midikey2hz;
attack = hslider("attack", 0.02, 0, 2, 0.01);
release = hslider("release", 0.6, 0, 2, 0.01);
gate = button("gate");
gain = hslider("gain",0.1,0,1,0.01);

env1 = gate : en.adsr(attack, 0, 1, release);
osc1 = os.oscsin(freq) * gain;
osc2 = os.oscsin(freq / 2) * gain;

osc = (osc1 + osc2) * env1;

echo (d,f) = + ~ (@(d) : *(f));

process = osc : echo(ma.SR / 4, 0.6) <: _,_;
