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

void sleepAnnouncement()
{
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 40);
  display.print("z");
  display.display();
  delay(200);

  display.setTextSize(2);
  display.print("z");
  display.display();
  delay(200);

  display.setTextSize(3);
  display.print("z");
  display.display();
  delay(500);

  display.setTextSize(3);

  display.setCursor(40, 80);
  display.print("z");
  display.display();
  delay(200);

  display.setTextSize(4);
  display.print("z");
  display.display();
  delay(200);

  display.setTextSize(5);
  display.print("z");
  display.display();
  delay(1000);
}
