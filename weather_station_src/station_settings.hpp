/*
This file contains general settings for using the weather station.

Assuming the code is untouched, the needed libraries installed, and
the correct board configurations chosen in the Arduino IDE (board type, com port);
the below settings are all that should be needed to get the project running for a new
user/location.
*/

#ifndef _STATION_SETTINGS_HPP_
#define _STATION_SETTINGS_HPP_

//WiFi Settings - Update the below to your local WiFi
#define WIFI_SSID ""
#define WIFI_PASS ""

//Location and OpenWeatherMap Settings
//How to get APIKEY and find CITY_ID: https://www.dmopress.com/openweathermap-howto/
#define OWM_APIKEY ""
#define CITY_ID    ""
#define ALTITUDE   (0.0)

#endif //_STATION_SETTINGS_HPP_