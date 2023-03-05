#include "timer_functions.h"
#include "constants.h"
void displayLoading();
void sleepAnnouncement(int seconds_to_sleep);
void displayInit();
void displayInfo(bool online, bool watering_time, Time time, int &flashcounter, int moisture_Percentage_1, int moisture_Percentage_2, waterlevel water_level);
void displayText(const char *message);
