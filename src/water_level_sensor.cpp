#include <Arduino.h>

int getWaterLevel(int GPIO_pin, int POWER_IN)
{
  digitalWrite(POWER_IN, HIGH);
  delay(10);
  int read_value = analogRead(GPIO_pin);
  delay(10);
  digitalWrite(POWER_IN, LOW);
  // int moisture_Percentage = map(read_value, minMoisture, maxMoisture, 0, 100);
  return read_value;
};