import("stdfaust.lib");

envelope = en.adsr(attack, decay, sustain, release, gate) * gain
with {
    attack = hslider("attack", 0.02, 0, 2, 0.01);
    decay = hslider("decay", 0.01, 0, 1, 0.01);
    sustain = hslider("sustain", 1, 0, 1, 0.01);
    release = hslider("release", 0.6, 0, 2, 0.01);
    gate = button("gate");
    gain = hslider("gain", 0.1, 0, 1, 0.01);
};

freq = hslider("freq",60,20,20000,0.01) : ba.midikey2hz;

env = gate : en.adsr(attack, 0, 1, release);

process = os.oscsin(freq) * envelope <: _,_;
