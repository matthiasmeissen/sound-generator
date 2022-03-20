import("stdfaust.lib");

envelope = en.adsr(attack, decay, sustain, release, gate) * gain
with {
    attack = hslider("[1]attack", 50, 0.01, 1000, 1) * 0.001;
    decay = hslider("[2]decay", 50, 0.01, 1000, 1) * 0.001;
    sustain = hslider("[3]sustain", 0.8, 0, 1, 0.01);
    release = hslider("[4]release", 50, 0.01, 1000, 1) * 0.001;
    gate = button("gate");
    gain = hslider("[5]gain", 0.2, 0, 1, 0.01);
};

freq = hslider("[6]freq",60,20,20000,0.01) : ba.midikey2hz;

osc = os.oscsin(freq), os.square(freq), os.sawtooth(freq), os.triangle(freq) : ba.selectn(4, num)
with {
    num = nentry("Oscillator", 0, 0, 3, 1);
};

process = osc * envelope <: _,_;
