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
#include "deep_sleep.h"
#include "oled_functions.h"
#include "moisture_sensor.h"
#include "water_level_sensor.h"

#define AOUT_PIN_MOISTURE_1 32

#define AOUT_PIN_W_LEVEL_1 33
#define W_LEVEL_POWER 25
#define PUMP_1_POWER 26

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
  pinMode(PUMP_1_POWER, OUTPUT);

  // ++bootCount;
  // Serial.println("Boot number: " + String(bootCount));

  // Print the wakeup reason for ESP32
  print_wakeup_reason();

  /*
  First we configure the wake up source
  We set our ESP32 to wake up every 5 seconds
  */
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  // Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  //                " Seconds");

  // Serial.println("Going to sleep now");
  // delay(1000);
  // Serial.flush();
  // esp_deep_sleep_start();
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
  delay(400);
  send_sleeping();
};
