/*
ESP32 Weather Station Project
Originally produced by educ8s.tv at: http://educ8s.tv/esp32-weather-station

This implementation uses nearly all of educ8s.tv's original code with changes for:
* Improving code readability by moving groups of functionaliy to dedicated files
* Code comments to help explain more complex portions of the code

*/

#define ARDUINOJSON_ENABLE_PROGMEM 0

#include <WiFi.h>
#include "Adafruit_BME280.h"
#include "station_settings.hpp"
#include "nextion_helpers.hpp"
#include "bme280_helpers.hpp"
#include "hw_defs.hpp"

//prototypes
void connectToWifi(void);
void initBME280(void);
void blinkLED(void);

//globals
int iterations = 1800;
int weatherID = 0;
Adafruit_BME280 bme(I2C_SDA, I2C_SCL);

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(UART_BAUD);
  initBME280();
  connectToWifi();
}

void loop()
{
  //Wait a couple seconds before updating sensor data
  delay(2000);

  //Update weather forecast every hour
  if(iterations == 1800)
  {
    getWeatherData(weatherID);
    printWeatherIcon(weatherID);
    iterations = 0;
  }

  sendTemperatureToNextion(getTemperature(bme));
  sendHumidityToNextion(getHumidity(bme));
  sendPressureToNextion(getPressure(bme));

  iterations++;
  blinkLED();
}

void connectToWifi(void)
{
  WiFi.enableSTA(true); //set wifi board into station mode
  delay(2000); //wait a moment after config before starting WiFi
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}

void initBME280(void)
{
  bool status = bme.begin(BME280_ADDRESS);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void blinkLED(void)
{
  digitalWrite(LED_PIN,HIGH);
  delay(100);
  digitalWrite(LED_PIN,LOW);
}
