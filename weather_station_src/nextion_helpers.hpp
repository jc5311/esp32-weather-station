// This file contains helper methods for updating the Nextion display.

#ifndef _NEXTION_HELPERS_HPP_
#define _NEXTION_HELPERS_HPP_

void getWeatherData(int &weatherID);
void sendHumidityToNextion(float humidity);
void sendTemperatureToNextion(float temperature);
void sendPressureToNextion(float pressure);
void showConnectingIcon(void);
void endNextionCommand(void);
void printWeatherIcon(int id);
void drawFog(void);
void drawHeavySnowfall(void);
void drawModerateSnowfall(void);
void drawLightSnowfall(void);
void drawHeavyRain(void);
void drawModerateRain(void);
void drawLightRain(void);
void drawLightRainWithSunOrMoon(void);
void drawThunderstorm(void);
void drawClearWeather(void);
void drawCloud(void);
void drawFewClouds(void);
#endif //_NEXTION_HELPERS_HPP_