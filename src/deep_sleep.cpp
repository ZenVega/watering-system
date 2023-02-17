#include <Arduino.h>
#include "oled_functions.h"
#include "constants.h"
#include "watering.h"
#include "timer_functions.h"

void send_sleeping()
{
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, HIGH);
  sleepAnnouncement();
  sleepAnnouncement();
  esp_deep_sleep_start();
}

void wake_up_and_react()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Wakeup caused by external signal using RTC_IO");
    waterForSeconds(PUMP_1_SIGNAL, 3);
    break;
  case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Wakeup caused by external signal using RTC_CNTL");
    break;
  case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Wakeup caused by timer");
    break;
  case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Wakeup caused by touchpad");
    break;
  case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Wakeup caused by ULP program");
    break;
  default:
    Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
    break;
  }
};

int getSecondsTillWakeUp()
{
  int minutes_remaining;
  Time current_time = getTime();

  if (current_time.hours >= START_WATERING_TIME)
  {
    // get minutes till midnight
    Serial.print(current_time.hours);
    Serial.print(":");
    Serial.print(current_time.minutes);
    Serial.println(" Uhr");
    minutes_remaining = (24 * 60) - (current_time.minutes) - (current_time.hours * 60);
    Serial.print(minutes_remaining);
    Serial.println(" minutes till midnight");
    minutes_remaining += (START_WATERING_TIME * 60);
  }
  else
  {
    minutes_remaining = (START_WATERING_TIME * 60) - current_time.minutes - (current_time.hours * 60);
  }
  Serial.print(minutes_remaining);
  Serial.println(" minutes left");
  return minutes_remaining;
}