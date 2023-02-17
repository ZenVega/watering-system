#include <Arduino.h>
#include <WiFi.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "constants.h"
#include "secrets.h"

#include "timer_functions.h"
#include "deep_sleep.h"
#include "oled_functions.h"
#include "sensors/moisture_sensor.h"
#include "sensors/water_level_sensor.h"
#include "watering.h"

// RTC_DATA_ATTR int bootCount = 0;

using namespace std;

const char *ssid = SECRET_SSID;
const char *password = SECRET_PASS;

int start_watering_time = 19;
int end_watering_time = 20;
bool online = false;
int flashcounter = 0;

void setup()
{
  Serial.begin(9600);

  displayInit();
  displayLoading();
  delay(500);
  print_wakeup_reason();

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
  online = true;
  delay(500);

  // Define Power Output Pins
  pinMode(W_LEVEL_POWER, OUTPUT);
  pinMode(PUMP_1_SIGNAL, OUTPUT);
};

void loop()
{

  Time time = getTime();
  string time_string;
  boolean watering_time = isWateringTime(time.hours, start_watering_time, end_watering_time);

  int moisture_Percentage = readSensor(AOUT_PIN_MOISTURE_1);
  // Serial.print("Moisture: ");
  // Serial.print(moisture_Percentage);
  // Serial.println("%");

  int water_level = getWaterLevel(AOUT_PIN_W_LEVEL_1, W_LEVEL_POWER);
  // Serial.print("Water-Level: ");
  // Serial.println(water_level);

  // Serial.println("_______________________________________");
  displayInfo(online, watering_time, time, flashcounter, moisture_Percentage, water_level);
  // waterForSeconds(PUMP_1_SIGNAL, 4);
  delay(400);
  // send_sleeping();
};
