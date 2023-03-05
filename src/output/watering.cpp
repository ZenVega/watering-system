#include <Arduino.h>
#include "constants.h"
#include "oled_functions.h"
#include "deep_sleep.h"
#include "sensors/moisture_sensor.h"

void start_watering(int PIN)
{
  digitalWrite(PIN, HIGH);
}

void stop_watering(int PIN)
{
  digitalWrite(PIN, LOW);
}

void waterForSeconds(int PIN, int seconds)
{
  Serial.println("Start watering");
  start_watering(PIN);
  delay(seconds * mS_TO_S_FACTOR);
  Serial.println("End watering");
  stop_watering(PIN);
  delay(1 * mS_TO_S_FACTOR);
}

void flashLEDs()
{
  pinMode(REFILL_LED, OUTPUT);
  digitalWrite(REFILL_LED, HIGH);
  delay(500);
  digitalWrite(REFILL_LED, LOW);
  delay(500);
}

void wateringRoutine()
{
  bool more_water = true;
  Serial.println("WateringTime");
  for (int i = 0; i < MAX_WATERING_REPITITIONS; i++)
  {
    if (more_water)
    {
      displayText("SPLISH \n   SPLASH!");
      waterForSeconds(PUMP_1_SIGNAL, SECONDS_WATERING);
      int moisture_percentage_1 = readSensor(AOUT_PIN_MOISTURE_1);
      int moisture_percentage_2 = readSensor(AOUT_PIN_MOISTURE_2);
      boolean go_on_watering = confirm_watering(moisture_percentage_1, moisture_percentage_2);
      if (go_on_watering)
      {
        more_water = false;
      }
    }
  }
}