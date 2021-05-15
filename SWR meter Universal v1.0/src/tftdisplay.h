/**
 * 
 * ESP32-based 2KW SWR/Power meter AD8310 based
 * Project description http://vk6nx.net/06_projects.html
 * Source code: http://github.com/VK6NX/PAcontrol
 * 
 * 
 *
 * tftdisplay.h  
 *
 */

#ifndef TFTDISPLAY_H_
#define TFTDISPLAY_H_

#include <Adafruit_GFX.h>                 // Core graphics library
#include <Adafruit_ST7735.h>              // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h>              // Hardware-specific library for ST7789

#define TFT_RST       15               // TFT display pin RST
#define TFT_DC        17              // TFT display pin DC
#define TFT_CS        16              // TFT display pin CS

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
uint8_t displayRefreshFlags = 0;
#define DISPLAY_REFRESH_SWR 0x08

void displayInit(){
  tft.initR(INITR_BLACKTAB);                  // initialise TFT screen
  tft.setRotation(3);                         // rotate screen CW 270
  tft.fillScreen(ST77XX_BLACK);

  // Displays SWR
  tft.setCursor(5, 15);                       // set text to coordinates 5 = from left, 10 = from top
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);                         // set the font x2
  tft.println("SWR");
  // Displays Power
  tft.setCursor(5, 40);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.println("PWR");
  // Displays W
  tft.setCursor(140, 40);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.println("W");
  // Displays dBm
  tft.setCursor(5, 95);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.println("dBm");
}

#endif /* TFTDISPLAY_H_ */