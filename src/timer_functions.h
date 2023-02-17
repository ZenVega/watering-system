
struct Time
{
  int hours;
  int minutes;
};

int getHour();
Time getTime();
boolean isWateringTime(int current_hour, int minTime, int maxTime);