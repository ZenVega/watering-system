#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "timer_functions.h"
#include <string>

using namespace std;

Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                        OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void displayInit()
{
  display.begin(0x3D, true); // Address 0x3D default
  display.setRotation(1);
  display.setTextSize(2);
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.display();
};

void displayLoading()
{
  display.clearDisplay();
  display.setCursor(0, 40);
  display.print("connecting...");
  display.display();
};

void displayInfo(bool online, bool watering_time, Time time, int &flashcounter, int moisture_Percentage_1, int moisture_Percentage_2, waterlevel water_level)
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
  display.setCursor(0, 5);
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
  display.setCursor(0, 25);
  display.print("M1: ");
  display.print(moisture_Percentage_1);
  display.println("%");

  display.setCursor(0, 45);
  display.print("M2: ");
  display.print(moisture_Percentage_2);
  display.println("%");

  display.setCursor(0, 65);
  display.print("tank: ");
  if (water_level == full)
  {
    display.println("full");
  }
  else if (water_level == low)
  {
    display.println("low");
  }
  else
  {
    display.println("EMPTY!");
  }
  display.display();
};

void sleepAnnouncement(int seconds_to_sleep)
{
  display.clearDisplay();
  display.setTextSize(1.7);
  display.setCursor(0, 3);
  display.print("sleeping for");
  display.setCursor(0, 16);
  display.print(seconds_to_sleep / 60 / 60);
  display.println(" hours");
  display.display();

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
  display.clearDisplay();
}

void displayText(const char *message)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 40);
  display.print(message);
  display.display();
}