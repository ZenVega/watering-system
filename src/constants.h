#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define mS_TO_S_FACTOR 1000       /* Conversion factor for milli seconds to seconds */

#define GPIO_INTERRUPT GPIO_NUM_12
#define GPIO_OLED_VCC 13
#define AOUT_PIN_MOISTURE_1 32
#define AOUT_PIN_W_LEVEL_1 33
#define W_LEVEL_POWER 25
#define PUMP_1_SIGNAL 26
#define REFILL_LED 27

#define START_WATERING_TIME 20
#define END_WATERING_TIME 22

#define MIN_MOISTURE_PERCENTAGE 25
#define STOP_WATERING_MOISTURE_PERCENTAGE 30
#define MAX_WATERING_REPITITIONS 3
#define SECONDS_WATERING 3
#define MINUTES_SLEEP_AFTER_WATERING 10
#define MINUTES_SLEEP_EMPTY_TANK 60

// OLED CONSTANTS

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 16
#define OLED_CS 5
#define OLED_RESET -1

struct Time
{
  int hours;
  int minutes;
};

enum waterlevel
{
  full,
  low,
  empty
};

enum sleeptimer
{
  after_watering,
  empty_tank,
  till_next_watering_time
};

#endif
