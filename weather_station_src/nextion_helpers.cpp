#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "station_settings.hpp"
#include "nextion_helpers.hpp"

#define OWM_SERVERNAME "api.openweathermap.org"

void getWeatherData(int &weatherID) //client function to send/receive GET request data.
{
  WiFiClient client;
  if (!client.connect(OWM_SERVERNAME, 80 /*port 80*/))
    return;

  // We now create a URI for the request
  String url = "/data/2.5/forecast?id=" + String(CITY_ID) + "&units=metric&cnt=1&APPID=" + String(OWM_APIKEY);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + String(OWM_SERVERNAME) + "\r\n" +
                "Connection: close\r\n\r\n");
  
  //wait for data to become available
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    //if we timeout, disconnect from the server and abort
    if (millis() - timeout > 5000)
    {
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from the server
  String result ="";
  while(client.available())
      result = client.readStringUntil('\r');

  //prep the json data for deserialization
  result.replace('[', ' ');
  result.replace(']', ' ');

  //convert the json data into a C-style string, make sure to null terminate it
  char jsonArray [result.length()+1];
  result.toCharArray(jsonArray,sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';

  //now deserialize the data and place it in our json_doc object
  StaticJsonDocument<1024> json_doc;
  DeserializationError error = deserializeJson(json_doc, jsonArray);
  if (error)
    Serial.println("deserializeJson() failed");
  //if deserialization succeeded, extract and store the forecast ID
  else
  {
    String idString = json_doc["list"]["weather"]["id"];
    weatherID = idString.toInt();
    Serial.print("\nWeatherID: ");
    Serial.print(weatherID);
  }

  endNextionCommand(); //We need that in order the nextion to recognise the first command after the serial print
  client.stop();
}

void showConnectingIcon(void)
{
  Serial.println();
  String command = "weatherIcon.pic=3";
  Serial.print(command);
  endNextionCommand();
}

void sendHumidityToNextion(float humidity)
{
  String command = "humidity.txt=\""+String(humidity,1)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void sendTemperatureToNextion(float temperature)
{
  String command = "temperature.txt=\""+String(temperature,1)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void sendPressureToNextion(float pressure)
{
  String command = "pressure.txt=\""+String(pressure,1)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void endNextionCommand(void)
{
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void printWeatherIcon(int id)
{
  switch(id)
  {
    case 800: drawClearWeather(); break;
    case 801: drawFewClouds(); break;
    case 802: drawFewClouds(); break;
    case 803: drawCloud(); break;
    case 804: drawCloud(); break;

    case 200: drawThunderstorm(); break;
    case 201: drawThunderstorm(); break;
    case 202: drawThunderstorm(); break;
    case 210: drawThunderstorm(); break;
    case 211: drawThunderstorm(); break;
    case 212: drawThunderstorm(); break;
    case 221: drawThunderstorm(); break;
    case 230: drawThunderstorm(); break;
    case 231: drawThunderstorm(); break;
    case 232: drawThunderstorm(); break;

    case 300: drawLightRain(); break;
    case 301: drawLightRain(); break;
    case 302: drawLightRain(); break;
    case 310: drawLightRain(); break;
    case 311: drawLightRain(); break;
    case 312: drawLightRain(); break;
    case 313: drawLightRain(); break;
    case 314: drawLightRain(); break;
    case 321: drawLightRain(); break;

    case 500: drawLightRainWithSunOrMoon(); break;
    case 501: drawLightRainWithSunOrMoon(); break;
    case 502: drawLightRainWithSunOrMoon(); break;
    case 503: drawLightRainWithSunOrMoon(); break;
    case 504: drawLightRainWithSunOrMoon(); break;
    case 511: drawLightRain(); break;
    case 520: drawModerateRain(); break;
    case 521: drawModerateRain(); break;
    case 522: drawHeavyRain(); break;
    case 531: drawHeavyRain(); break;

    case 600: drawLightSnowfall(); break;
    case 601: drawModerateSnowfall(); break;
    case 602: drawHeavySnowfall(); break;
    case 611: drawLightSnowfall(); break;
    case 612: drawLightSnowfall(); break;
    case 615: drawLightSnowfall(); break;
    case 616: drawLightSnowfall(); break;
    case 620: drawLightSnowfall(); break;
    case 621: drawModerateSnowfall(); break;
    case 622: drawHeavySnowfall(); break;

    case 701: drawFog(); break;
    case 711: drawFog(); break;
    case 721: drawFog(); break;
    case 731: drawFog(); break;
    case 741: drawFog(); break;
    case 751: drawFog(); break;
    case 761: drawFog(); break;
    case 762: drawFog(); break;
    case 771: drawFog(); break;
    case 781: drawFog(); break;

    default:break; 
  }
}

void drawFog(void)
{
  String command = "weatherIcon.pic=13";
  Serial.print(command);
  endNextionCommand();
}

void drawHeavySnowfall(void)
{
  String command = "weatherIcon.pic=8";
  Serial.print(command);
  endNextionCommand();
}

void drawModerateSnowfall(void)
{
  String command = "weatherIcon.pic=8";
  Serial.print(command);
  endNextionCommand();
}

void drawLightSnowfall(void)
{
  String command = "weatherIcon.pic=11";
  Serial.print(command);
  endNextionCommand();
}

void drawHeavyRain(void)
{
  String command = "weatherIcon.pic=10";
  Serial.print(command);
  endNextionCommand();
}

void drawModerateRain(void)
{
  String command = "weatherIcon.pic=6";
  Serial.print(command);
  endNextionCommand();
}

void drawLightRain(void)
{
  String command = "weatherIcon.pic=6";
  Serial.print(command);
  endNextionCommand();
}

void drawLightRainWithSunOrMoon(void)
{
  String command = "weatherIcon.pic=7";
  Serial.print(command);
  endNextionCommand(); 
}

void drawThunderstorm(void)
{
  String command = "weatherIcon.pic=3";
  Serial.print(command);
  endNextionCommand();
}

void drawClearWeather(void)
{
  String command = "weatherIcon.pic=4";
  Serial.print(command);
  endNextionCommand();
}

void drawCloud(void)
{
  String command = "weatherIcon.pic=9";
  Serial.print(command);
  endNextionCommand();
}

void drawFewClouds(void)
{
  String command = "weatherIcon.pic=5";
  Serial.print(command);
  endNextionCommand(); 
}