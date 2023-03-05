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
#include "output/oled_functions.h"
#include "sensors/moisture_sensor.h"
#include "sensors/water_level_sensor.h"
#include "output/watering.h"

using namespace std;

const char *ssid = SECRET_SSID;
const char *password = SECRET_PASS;

bool online = false;
bool sleepInterruptor = false;
bool wakeInterruptor = false;
int flashcounter = 0;
int emptycounter = 0;

void IRAM_ATTR interruptCall()
{
  Serial.println("SleepInterruptor");
  sleepInterruptor = true;
}

void update_display(Time time)
{
  waterlevel water_level = getwaterlevel(AOUT_PIN_W_LEVEL_1, W_LEVEL_POWER);
  int moisture_Percentage_1 = readSensor(AOUT_PIN_MOISTURE_1);
  int moisture_Percentage_2 = readSensor(AOUT_PIN_MOISTURE_2);
  displayInfo(online, true, time, flashcounter, moisture_Percentage_1, moisture_Percentage_2, water_level);
};

void setup()
{
  Serial.begin(9600);
  pinMode(GPIO_OLED_VCC, OUTPUT);
  digitalWrite(GPIO_OLED_VCC, HIGH);

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
  pinMode(PUMP_1_SIGNAL, OUTPUT);
  pinMode(GPIO_INTERRUPT, PULLDOWN);
  wake_up_and_react(wakeInterruptor);
  attachInterrupt(GPIO_INTERRUPT, interruptCall, RISING);
  displayText("CALIMERA!");
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

  waterlevel water_level = getwaterlevel(AOUT_PIN_W_LEVEL_1, W_LEVEL_POWER);

  while (water_level == empty)
  {
    Serial.print("waterlevel: ");
    Serial.println(water_level);
    displayText("REFILL \nTANK!");
    flashLEDs();
    emptycounter++;
    water_level = getwaterlevel(AOUT_PIN_W_LEVEL_1, W_LEVEL_POWER);

    if (emptycounter > 10)
    {
      emptycounter = 0;
      send_sleeping(empty_tank);
    }
  }

  boolean watering_time = isWateringTime(time.hours, START_WATERING_TIME, END_WATERING_TIME);

  if (watering_time || wakeInterruptor)
  {
    update_display(time);

    if (wakeInterruptor)
    {
      Serial.println("WakeInterruptor");
      wakeInterruptor = false;
      delay(20000);
      send_sleeping(till_next_watering_time);
    }

    int moisture_Percentage_1 = readSensor(AOUT_PIN_MOISTURE_1);
    int moisture_Percentage_2 = readSensor(AOUT_PIN_MOISTURE_2);
    boolean watering_confirmed = confirm_watering(moisture_Percentage_1, moisture_Percentage_2);
    if (watering_confirmed)
    {
      wateringRoutine();
      update_display(time);
    }
    delay(10000);
    send_sleeping(after_watering);
  }

  if (!watering_time || sleepInterruptor)
  {
    send_sleeping(till_next_watering_time);
  }
};
