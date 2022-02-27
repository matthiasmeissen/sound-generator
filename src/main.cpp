#include <Arduino.h>

int number = 1;

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400);
}

void loop() {
  // Print number counting upwards
  Serial.println(number);
  number += 1;

  // Use the blink function to show LED
  blink();
}
