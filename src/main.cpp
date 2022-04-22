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

int freq;       // freq       Oscillator Freq       Midi notes
int osc;        // osc        Oscillator Type       0 - 4
int gate;       // gate       Trigger envelope      0 / 1
int att;        // attack     Attack envelope       0.01 - 1000
int rel;        // release    Release envelope      0.01 - 1000
int gain;       // gain       Gain Stereo           0 - 1


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

void redraw() {
  clearDisplay();
  compLabel(0, 0, "OSC");
  compSlider(0, 32, norm(gain), "LEV");
  compWaves(32, 0, osc);
  compKnob(32, 32, norm(att), "ATT");
  compKnob(64, 32, norm(rel), "REL");
  drawDisplay();
}

int allowRedraw = 0;


// Midi Handling

void OnNoteOn(byte channel, byte note, byte velocity) {
  freq = note;
  
  synthEngine.setParamValue("freq", freq);
  synthEngine.setParamValue("gate", 1);

  allowRedraw = 1;

  digitalWrite(LED_BUILTIN, HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  synthEngine.setParamValue("gate", 0);
  digitalWrite(LED_BUILTIN, LOW);
}

void OnControlChange(byte channel, byte control, byte value) {
  if (control == 100) {
    osc = value;
    synthEngine.setParamValue("osc", osc);
    report("Oscillator ", osc);
  }
  if (control == 101) {
    att = value;
    synthEngine.setParamValue("att", mapf(att, 0, 127, 0.01, 1000));
    report("Attack ", att);
  }
  if (control == 102) {
    rel = value;
    synthEngine.setParamValue("rel", mapf(rel, 0, 127, 0.01, 1000));
    report("Release ", rel);
  }
  if (control == 103) {
    gain = value;
    synthEngine.setParamValue("gain", norm(gain));
    report("Gain ", gain);
  }

  allowRedraw = 1;
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
  redraw();
}


// Runs often

void loop() {
  usbMIDI.read();

  if (millis() % 200 == 1 && allowRedraw) {
    redraw();
    allowRedraw = 0;
  } 
}
