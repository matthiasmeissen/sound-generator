import("stdfaust.lib");

freq = hslider("freq",440,20,20000,0.01);
gain = hslider("gain",1,0,1,0.01);

osc1 = os.oscsin(freq);

process = osc1 * gain;
