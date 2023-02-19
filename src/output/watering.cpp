#include <Arduino.h>
#include "constants.h"
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
      waterForSeconds(PUMP_1_SIGNAL, SECONDS_WATERING);
      int moisture_Percentage = readSensor(AOUT_PIN_MOISTURE_1);
      if (moisture_Percentage > STOP_WATERING_MOISTURE_PERCENTAGE)
      {
        more_water = false;
      }
    }
  }
}