#include <Arduino.h>
#include "constants.h"

waterlevel getwaterlevel(int GPIO_pin, int POWER_IN)
{
  int counter = 0;
  int minValue = 3000;
  waterlevel returnValue;

  while (counter < 5)
  {
    digitalWrite(POWER_IN, HIGH);
    delay(10);
    int read_value = analogRead(GPIO_pin);
    Serial.println(read_value);
    delay(10);
    digitalWrite(POWER_IN, LOW);

    if (read_value < minValue)
    {
      minValue = read_value;
    }
    counter++;
  }

  if (minValue > THRESHOLD_WATER_LEVEL_LOW)
  {
    returnValue = waterlevel::full;
  }
  else if (minValue > THRESHOLD_WATER_LEVEL_EMPTY)
  {
    returnValue = waterlevel::low;
  }
  else
  {
    returnValue = waterlevel::empty;
  }

  return returnValue;
};