#include <Arduino.h>
#include <MIDI.h>
#include <Audio.h>
#include "SoundEngine.h"

SoundEngine soundEngine;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(soundEngine,0,out,0);
AudioConnection patchCord1(soundEngine,0,out,1);

// SoundEngine Params
// freq - Midi notes converted to Frequency
// gate - Triggers the envelope
// gain - Gain of left and right Channels


void OnNoteOn(byte channel, byte note, byte velocity) {
  soundEngine.setParamValue("freq", note);
  soundEngine.setParamValue("gate", 1);
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  soundEngine.setParamValue("gate", 0);
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
