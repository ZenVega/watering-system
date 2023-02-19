#include <Arduino.h>
#include "constants.h"
#include "deep_sleep.h"

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
}
void flashLEDs()
{
  pinMode(REFILL_LED, OUTPUT);
  digitalWrite(REFILL_LED, HIGH);
  delay(500);
  digitalWrite(REFILL_LED, LOW);
  delay(500);
}
