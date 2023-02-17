#include <Arduino.h>
#include <tuple>
#include "time.h"
#include "constants.h"
#include "timer_functions.h"
#include <WiFi.h>

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

int getHour()
{
  int hour = 0;
  if (WiFi.status() == WL_CONNECTED)
  {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    hour = tm_struct->tm_hour;
  }
  return hour;
};

Time getTime()
{
  int hour = 0;
  int minutes = 0;
  if (WiFi.status() == WL_CONNECTED)
  {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    hour = tm_struct->tm_hour;
    minutes = tm_struct->tm_min;
  }
  return {hour, minutes};
};

boolean isWateringTime(int current_hour, int minTime, int maxTime)
{
  if (minTime <= current_hour && maxTime > current_hour)
  {
    return true;
  }
  else
  {
    return false;
  }
};
