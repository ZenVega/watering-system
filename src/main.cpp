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

using namespace std;

const char *ssid = SECRET_SSID;
const char *password = SECRET_PASS;

bool online = false;
bool sleepInterruptor = false;
int flashcounter = 0;

void IRAM_ATTR interruptCall()
{
  Serial.println("INTERRUPT");
  sleepInterruptor = true;
}

void setup()
{
  Serial.begin(9600);
  pinMode(GPIO_OLED_VCC, OUTPUT);
  digitalWrite(GPIO_OLED_VCC, HIGH);

  displayInit();
  displayLoading();
  delay(500);

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
  pinMode(GPIO_INTERRUPT, PULLDOWN);
  wake_up_and_react();
  attachInterrupt(GPIO_INTERRUPT, interruptCall, RISING);
  Serial.print("loading");
};

void loop()
{
  Time time = getTime();
  while (time.hours == 1 && time.minutes == 0)
  {
    Serial.print(".");
    delay(400);
    return;
  }
  Serial.println("");
  boolean watering_time = isWateringTime(time.hours, START_WATERING_TIME, END_WATERING_TIME);

  if (watering_time && !sleepInterruptor)
  {
    Serial.println("WateringTime");
    int moisture_Percentage = readSensor(AOUT_PIN_MOISTURE_1);

    int water_level = getWaterLevel(AOUT_PIN_W_LEVEL_1, W_LEVEL_POWER);
    displayInfo(online, watering_time, time, flashcounter, moisture_Percentage, water_level);
    delay(2000);
  }
  else
  {
    Serial.println("Sleeeeeping");
    sleepInterruptor = false;
    send_sleeping();
  }
};
