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

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Note Played");
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  digitalWrite(LED_BUILTIN, LOW);
  soundEngine.setParamValue("gate", 0);
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400);

  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.8);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
}

void loop() {
  usbMIDI.read();
}
