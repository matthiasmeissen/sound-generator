#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void initDisplay();
void drawDisplay();
void clearDisplay();
void compLabel(int posX, int posY, char* label);
void compKnob(int posX, int posY, float value, char* label);
void compSlider(int posX, int posY, float value, char* label);

#endif
