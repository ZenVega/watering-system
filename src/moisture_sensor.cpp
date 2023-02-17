#include <Arduino.h>

int readSensor(int GPIO_pin)
{
  int maxMoisture = 1000;
  int minMoisture = 2650;
  int read_value = analogRead(GPIO_pin); // read the analog value from sensor
  int moisture_Percentage = map(read_value, minMoisture, maxMoisture, 0, 100);
  return moisture_Percentage;
};