#include <Arduino.h>
#include <MIDI.h>
#include <Audio.h>
#include "SynthEngine.h"

SynthEngine synthEngine;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(synthEngine,0,out,0);
AudioConnection patchCord1(synthEngine,0,out,1);

// SynthEngine Params
// freq - Midi notes converted to Frequency
// gate - Triggers the envelope
// gain - Gain of left and right Channels


void OnNoteOn(byte channel, byte note, byte velocity) {
  synthEngine.setParamValue("freq", note);
  synthEngine.setParamValue("gate", 1);
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  synthEngine.setParamValue("gate", 0);
}

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.8);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);

  synthEngine.setParamValue("gain", 0.2);

  Serial.begin(38400);
}

void loop() {
  usbMIDI.read();
}
