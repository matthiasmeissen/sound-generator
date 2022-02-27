#include <Arduino.h>
#include <MIDI.h>

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void makeNote(int note, int duration) {
  usbMIDI.sendNoteOn(note, 127, 1);
  delay(duration);
  usbMIDI.sendNoteOff(note, 127, 1);

  Serial.println("Note played");
}

void setup() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400);
}

void loop() {
  // Uses the LED
  blink();

  // Plays a note
  makeNote(60, 800);
}
