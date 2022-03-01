#include <Arduino.h>
#include <MIDI.h>
#include <Audio.h>
#include "SineOscillator.h"

SineOscillator sineOscillator;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(sineOscillator,0,out,0);
AudioConnection patchCord1(sineOscillator,0,out,1);


void makeNote(int note, int duration) {
  usbMIDI.sendNoteOn(note, 127, 1);
  delay(duration);
  usbMIDI.sendNoteOff(note, 127, 1);

  Serial.println("Note played");
}

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.1);

  Serial.begin(38400);
}

void loop() {
  sineOscillator.setParamValue("freq",random(50,1000));
  delay(50);
}
