#include <Arduino.h>
#include <WiFi.h>
#include "timer_functions.h"
#include "moisture_sensor.h"
#include "water_level_sensor.h"

#define AOUT_PIN_MOISTURE_1 32

#define AOUT_PIN_W_LEVEL_1 33
#define W_LEVEL_POWER 25
#define PUMP_1_POWER 26

const char *ssid = "Healthy_Design_&_Sick_Machines";
const char *password = "Bakterien_und_Viren";

bool output = false;

void setup()
{
  Serial.begin(9600);

  // connect to WIFI
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Define Power Output Pins
  pinMode(W_LEVEL_POWER, OUTPUT);
  pinMode(PUMP_1_POWER, OUTPUT);
};

void loop()
{
  if (output)
  {
    digitalWrite(PUMP_1_POWER, HIGH);
    output = false;
  }
  else
  {
    digitalWrite(PUMP_1_POWER, LOW);
    output = true;
  }
  int currentHour = getHour();
  Serial.print(currentHour);
  Serial.println(" Hours");

  int moisture_Percentage = readSensor(AOUT_PIN_MOISTURE_1);
  Serial.print("Moisture: ");
  Serial.print(moisture_Percentage);
  Serial.println("%");

  int water_level = getWaterLevel(AOUT_PIN_W_LEVEL_1, W_LEVEL_POWER);
  Serial.print("Water-Level: ");
  Serial.println(water_level);

  Serial.println("_______________________________________");
  delay(1000);
};