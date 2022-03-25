#include "Display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void initDisplay() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
}

void updateDisplay() {
    display.display();
}

void clearDisplay() {
    display.clearDisplay();
}

void drawCircle(float r) {
  display.drawCircle(display.width()/2, display.height()/2, r, SSD1306_WHITE);

  display.fillCircle(display.width()/2, display.height()/2, r-8, SSD1306_WHITE);
}

void drawText() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Text"));
  
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println(200);
}

void drawLine() {
  display.drawLine(4, display.height()-4, display.width()-4, display.height()-4, SSD1306_WHITE);
}

void drawRectangle() {
  display.drawRect(4, 20, 20, 32, SSD1306_WHITE);
}
