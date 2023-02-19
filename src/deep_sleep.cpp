#include <Arduino.h>
#include "output/oled_functions.h"
#include "constants.h"
#include "output/watering.h"
#include "timer_functions.h"

void wake_up_and_react(bool &wakeInterruptor)
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_EXT0:
    wakeInterruptor = true;
    Serial.print("INTERRUPTOR");
    delay(1000);
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
    minutes_remaining = (24 * 60) - (current_time.minutes) - (current_time.hours * 60);
    minutes_remaining += (START_WATERING_TIME * 60);
  }
  else
  {
    minutes_remaining = (START_WATERING_TIME * 60) - current_time.minutes - (current_time.hours * 60);
  }
  Serial.print(minutes_remaining);
  Serial.println(" minutes till wake");
  return minutes_remaining * 60;
}

void send_sleeping(sleeptimer reason_to_sleep)
{
  int seconds_to_sleep;
  switch (reason_to_sleep)
  {
  case sleeptimer::after_watering:
    seconds_to_sleep = MINUTES_SLEEP_AFTER_WATERING * 60;
    break; // and exits the switch
  case sleeptimer::empty_tank:
    seconds_to_sleep = MINUTES_SLEEP_EMPTY_TANK * 60;
    break;
  case sleeptimer::till_next_watering_time:
    seconds_to_sleep = getSecondsTillWakeUp();
    break;
  }

  unsigned long long total_micro_seconds = seconds_to_sleep * uS_TO_S_FACTOR;
  esp_sleep_enable_timer_wakeup(seconds_to_sleep * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(GPIO_INTERRUPT, HIGH);
  Serial.print("sleeping for ");
  Serial.print(seconds_to_sleep / 60);
  Serial.println(" minutes");
  sleepAnnouncement(seconds_to_sleep);
  Serial.println("Ciao");
  digitalWrite(GPIO_OLED_VCC, LOW);
  esp_deep_sleep_start();
}