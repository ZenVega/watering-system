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
    delay(10);
    digitalWrite(POWER_IN, LOW);

    if (read_value < minValue)
    {
      minValue = read_value;
    }
    counter++;
  }

  if (minValue > 1000)
  {
    returnValue = waterlevel::full;
  }
  else if (minValue > 500)
  {
    returnValue = waterlevel::low;
  }
  else
  {
    returnValue = waterlevel::empty;
  }

  return returnValue;
};