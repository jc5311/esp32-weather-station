#include <Arduino.h>
#include "Adafruit_BME280.h"
#include "station_settings.hpp"
#include "bme280_helpers.hpp"

float getTemperature(Adafruit_BME280 &bme)
{
  return bme.readTemperature();
}

float getHumidity(Adafruit_BME280 &bme)
{
  return bme.readHumidity();
}

float getPressure(Adafruit_BME280 &bme)
{
  float pressure;
  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE,pressure);
  pressure = pressure/100.0F;

  return pressure;
}