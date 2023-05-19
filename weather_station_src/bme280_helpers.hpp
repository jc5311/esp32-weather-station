// This file contains helper methods for using the BME280 sensor.

#ifndef _BME_280_HELPERS_HPP_
#define _BME_280_HELPERS_HPP_

float getTemperature(Adafruit_BME280 &bme);
float getHumidity(Adafruit_BME280 &bme);
float getPressure(Adafruit_BME280 &bme);

#endif _BME_280_HELPERS_HPP_