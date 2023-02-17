#include <Arduino.h>
#include <iostream>
#include <vector>
using namespace std;

int readSensor(int GPIO_pin)
{
  int counter = 0;
  int average = 0;
  int maxMoisture = 1000;
  int minMoisture = 3000;
  vector<int> measurements;

  while (counter < 5)
  {
    int read_value = analogRead(GPIO_pin); // read the analog value from sensor
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