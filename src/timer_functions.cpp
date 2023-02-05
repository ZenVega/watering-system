#include <Arduino.h>
#include "time.h"
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
