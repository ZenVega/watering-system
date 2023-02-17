#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "timer_functions.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 16
#define OLED_CS 5
#define OLED_RESET -1

using namespace std;

Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                        OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void displayInit()
{
  display.begin(0x3D, true); // Address 0x3D default
  display.clearDisplay();
};

void displayLoading()
{
  display.clearDisplay();
  display.setCursor(0, 40);
  display.print("connecting...");
  display.display();
};

void displayInfo(bool online, bool watering_time, Time time, int &flashcounter, int moisture_Percentage, int water_level)
{
  display.clearDisplay();
  display.drawChar(116, 0, 0x9D, SH110X_WHITE, SH110X_BLACK, 2, 2);

  if (watering_time == true)
  {
    if (flashcounter > 10)
    {
      flashcounter = 0;
    }
    if (flashcounter > 5)
    {
      display.drawChar(100, 0, 0xF6, SH110X_WHITE, SH110X_BLACK, 2, 2);
    }
    flashcounter++;
  }

  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  if (time.hours < 10)
  {
    display.print("0");
  }
  display.print(time.hours);
  display.print(":");
  if (time.minutes < 10)
  {
    display.print("0");
  }
  display.println(time.minutes);

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("moist: ");
  display.print(moisture_Percentage);
  display.println("%");

  display.setCursor(0, 40);
  display.print("tank: ");
  display.println(water_level);

  display.display();
};

// Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT,
//                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// This is the library: https://learn.adafruit.com/adafruit-monochrome-1-12-in-128x128-oled/arduino

// const unsigned char online_icon[] PROGMEM = {
//     B11110111, B10000000,
//     B11100011, B10000000,
//     B11110111, B10000000,
//     B11000001, B10000000,
//     B11110111, B10000000,
//     B10000000, B10000000,
//     B11110111, B10000000,
//     B11110111, B10000000};

// void AllWhite(Adafruit_SH1107 display)
// {
//   int16_t i;
//   int16_t j;
//   display.clearDisplay();

//   for (i = 0; i < 128; i++)
//   {
//     for (j = 0; j < 128; j++)
//     {
//       display.drawPixel(j, i, SH110X_WHITE);
//     }
//     display.display();
//     delay(1000);
//   }
// };

// void TextDisplay(Adafruit_SH1107 display)
// {
//   display.clearDisplay();
//   display.drawBitmap(5, 30, online_icon, 9, 8, SH110X_BLACK);
//   display.display();
//   delay(1);
//   display.setTextSize(3);
//   display.setTextColor(SH110X_WHITE);
//   display.setCursor(5, 40);
//   display.println("Hello World");
//   display.display();
//   delay(1500);
// };

// void AllBlack(Adafruit_SH1107 display)
// {
//   int16_t i;
//   int16_t j;
//   display.clearDisplay();
//   for (i = 0; i < 128; i++)
//   {
//     for (j = 0; j < 128; j++)
//     {
//       display.drawPixel(j, i, SH110X_BLACK);
//     }
//     display.display();
//     delay(1000);
//   }
// };

// void testfillrect(Adafruit_SH1107 display)
// {
//   display.clearDisplay();

//   for (int16_t i = 0; i < display.height() / 2; i += 3)
//   {
//     // The INVERSE color is used so rectangles alternate white/black
//     display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, SH110X_INVERSE);
//     display.display(); // Update screen with each newly-drawn rectangle
//     delay(1);
//   }

//   delay(2000);
// };

// void displayInfo(Adafruit_SH1107 display, bool online)
// {
//   display.clearDisplay();
//   display.setTextSize(2);
//   // display.drawChar(0, 0, 150, SH110X_BLACK, SH110X_WHITE, 10, 10);
//   display.setTextColor(SH110X_WHITE);
//   display.setCursor(5, 40);
//   display.println("Hello World");
//   display.display();
// };