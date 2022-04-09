import("stdfaust.lib");

freq = hslider("[1]freq",60,0,127,1) : ba.midikey2hz;

osc = os.oscsin(freq), os.triangle(freq), os.sawtooth(freq), os.square(freq), no.noise : ba.selectn(5, num)
with {
    num = nentry("[2]osc", 0, 0, 4, 1);
};

envelope = gate : en.adsr(attack, 0.001, 1, release) * gain
with {
    gate = button("[3]gate");
    attack = hslider("[4]att", 50, 0.01, 1000, 1) * 0.001;
    release = hslider("[5]rel", 50, 0.01, 1000, 1) * 0.001;
    gain = hslider("[6]gain", 0.2, 0, 1, 0.01);
};

process = osc * envelope <: _,_;
