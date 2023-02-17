#include <Arduino.h>
#include <WiFi.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "secrets.h"
#include "timer_functions.h"
#include "moisture_sensor.h"
#include "water_level_sensor.h"
#include "oled_functions.h"

#define AOUT_PIN_MOISTURE_1 32

#define AOUT_PIN_W_LEVEL_1 33
#define W_LEVEL_POWER 25
#define PUMP_1_POWER 26

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 16
#define OLED_CS 5
#define OLED_RESET -1

using namespace std;

// Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT,
//                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const char *ssid = SECRET_SSID;
const char *password = SECRET_PASS;

bool output = false;
bool online = false;
int flashcounter = 0;

void setup()
{
  Serial.begin(9600);

  displayInit();
  // display.begin(0x3D, true); // Address 0x3D default
  // display.clearDisplay();
  displayLoading();

  // connect to WIFI
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  delay(500);

  // Define Power Output Pins
  pinMode(W_LEVEL_POWER, OUTPUT);
  pinMode(PUMP_1_POWER, OUTPUT);
};

void loop()
{

  Time time = getTime();
  string time_string;

  int moisture_Percentage = readSensor(AOUT_PIN_MOISTURE_1);
  // Serial.print("Moisture: ");
  // Serial.print(moisture_Percentage);
  // Serial.println("%");

  int water_level = getWaterLevel(AOUT_PIN_W_LEVEL_1, W_LEVEL_POWER);
  // Serial.print("Water-Level: ");
  // Serial.println(water_level);

  // Serial.println("_______________________________________");
  displayInfo(true, true, time, flashcounter, moisture_Percentage, water_level);
  delay(100);
};
