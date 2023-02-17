#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define mS_TO_S_FACTOR 1000    /* Conversion factor for milli seconds to seconds */

#define AOUT_PIN_MOISTURE_1 32
#define AOUT_PIN_W_LEVEL_1 33
#define W_LEVEL_POWER 25
#define PUMP_1_SIGNAL 26

#define START_WATERING_TIME 1
#define END_WATERING_TIME 2

struct Time
{
  int hours;
  int minutes;
};

#endif
