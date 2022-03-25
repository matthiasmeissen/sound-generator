#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void initDisplay();
void updateDisplay();
void clearDisplay();
void drawCircle(float r);
void drawText();
void drawLine();
void drawRectangle();

#endif
