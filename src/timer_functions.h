#ifndef MYSTRUCT_H
#define MYSTRUCT_H
struct Time
{
  int hours;
  int minutes;
};

#endif

int getHour();
Time getTime();
boolean isWateringTime(int current_hour, int minTime, int maxTime);