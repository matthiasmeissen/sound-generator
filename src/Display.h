#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void initDisplay();
void drawDisplay();
void clearDisplay();
void drawCircle(float r);
void drawText(float num);
void drawLine();
void drawRectangle();
void drawLevel(int posX, int posY, float value);

#endif
