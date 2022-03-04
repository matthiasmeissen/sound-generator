#include <Arduino.h>
#include <MIDI.h>
#include <Audio.h>
#include "SineOscillator.h"

SineOscillator sineOscillator;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(sineOscillator,0,out,0);
AudioConnection patchCord1(sineOscillator,0,out,1);

// SineOscillator Params
// freq - Midi notes converted to Frequency
// gate - Triggers the envelope
// gain - Gain of left and right Channels


void OnNoteOn(byte channel, byte note, byte velocity) {
  sineOscillator.setParamValue("freq", note);
  sineOscillator.setParamValue("gate", 1);
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  sineOscillator.setParamValue("gate", 0);
}

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.8);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);

  Serial.begin(38400);
}

void loop() {
  usbMIDI.read();
}
