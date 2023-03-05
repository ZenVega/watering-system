#include <Arduino.h>
#include <iostream>
#include <vector>
#include "constants.h"
using namespace std;

int readSensor(int GPIO_pin)
{
  int counter = 0;
  int average = 0;
  int maxMoisture = 1000;
  int minMoisture = 2500;
  vector<int> measurements;

  while (counter < 5)
  {
    int read_value = analogRead(GPIO_pin); // read the analog value from sensor
    Serial.print("moisture: ");
    Serial.println(read_value);
    measurements.push_back(read_value);
    counter++;
  }

  for (const int &i : measurements)
  {
    average += i;
  }
  average = average / measurements.size();
  int moisture_Percentage = map(average, minMoisture, maxMoisture, 0, 100);
  return moisture_Percentage;
};

boolean confirm_watering(int moisture_percentage_1, int moisture_percentage_2)
{
  if (
      (moisture_percentage_1 < MIN_MOISTURE_PERCENTAGE && moisture_percentage_2 < DONT_WATER_THRESHOLD) ||
      (moisture_percentage_2 < MIN_MOISTURE_PERCENTAGE && moisture_percentage_1 < DONT_WATER_THRESHOLD))
  {
    Serial.println("water");
    return true;
  }
  else
  {
    Serial.println("dont water");
    return false;
  }
};