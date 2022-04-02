#include <Arduino.h>
#include <MIDI.h>
#include <Audio.h>
#include "Display.h"
#include "SynthEngine.h"

SynthEngine synthEngine;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(synthEngine,0,out,0);
AudioConnection patchCord1(synthEngine,0,out,1);


// SynthEngine Params

float freq;       // freq       Oscillator Freq       Midi notes
float attack;     // attack     Attack envelope       0 - 2
float release;    // release    Release envelope      0 - 2
int gate;         // gate       Trigger envelope      0 / 1
float ampsine;    // ampsine    Amplitude SineOsc     0 - 1
float amptri;     // amptri     Amplitude TriOsc      0 - 1
float ampsquare;  // ampsquare  Amplitude SquareOsc   0 - 1
float gain;       // gain       Gain Stereo           0 - 1


// Utility Functions

// mapf
// lets you map a float value to a specific range

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// norm
// Maps a number ranging from 0-127 to 0-1

float norm(int x) {
  return (x - 0.0) * (1.0 - 0.0) / (127.0 - 0.0) + 0.0;
}

// midiToRange
// Maps a number ranging from 0-127 to a specific range

float midiToRange(int x, float out_min, float out_max) {
  return (x - 0.0) * (out_max - out_min) / (127.0 - 0.0) + out_min;
}

void report(char* label, float value) {
  Serial.print(label);
  Serial.println(value);
}


// Screen Functions

void updateScreen() {
  clearDisplay();
  drawLevel(20, 20, attack);
  drawDisplay();
}


// Midi Handling

void OnNoteOn(byte channel, byte note, byte velocity) {
  freq = note;

  synthEngine.setParamValue("freq", freq);
  synthEngine.setParamValue("gate", 1);

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Note Played");
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  digitalWrite(LED_BUILTIN, LOW);
  synthEngine.setParamValue("gate", 0);
}

void OnControlChange(byte channel, byte control, byte value) {
  if (control == 100) {
    attack = norm(value);
    synthEngine.setParamValue("attack", attack);
    report("Attack", attack);
  }
  if (control == 101) {
    float val = norm(value);
    synthEngine.setParamValue("release", val);
    report("Release ", val);
  }
  if (control == 102) {
    float val = norm(value);
    synthEngine.setParamValue("ampsine", val);
    report("Amp Sine ", val);
  }
  if (control == 103) {
    float val = norm(value);
    synthEngine.setParamValue("amptri", val);
    report("Amp Tri ", val);
  }
  if (control == 104) {
    float val = norm(value);
    synthEngine.setParamValue("ampsquare", val);
    report("Amp Square ", val);
  }
}


// Runs once when loaded

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400);
  
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.8);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleControlChange(OnControlChange);


  initDisplay();
  updateScreen();
  drawDisplay();
}


// Runs often

void loop() {
  usbMIDI.read();

  if (millis() % 100 == 1) {
    updateScreen();
  }
  
}
