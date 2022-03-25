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
//
// freq       Oscillator Freq       Midi notes

float freq;

// attack     Attack envelope       0 - 2
// release    Release envelope      0 - 2
// gate       Trigger envelope      0 / 1
// ampsine    Amplitude SineOsc     0 - 1
// amptri     Amplitude TriOsc      0 - 1
// ampsquare  Amplitude SquareOsc   0 - 1
// gain       Gain Stereo           0 - 1


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

float midiToRange(int x, float out_min, float out_max) {
  return (x - 0.0) * (out_max - out_min) / (127.0 - 0.0) + out_min;
}

void report(char* label, float value) {
  Serial.print(label);
  Serial.println(value);
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
    float val = norm(value);
    synthEngine.setParamValue("attack", val);
    report("Attack ", val);
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
}


// Runs often

void loop() {
  clearDisplay();

  usbMIDI.read();

  drawCircle(20);
  drawText(freq);
  drawLine();
  drawRectangle();

  updateDisplay();
}
