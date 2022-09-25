#ifndef __DATA_ASYNC_H__
#define __DATA_ASYNC_H__
#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include "SPIFFS.h"
#include "log.h"

AsyncWebServer server (80);

#define LED_1 25
#define LED_2 2
const char* PARAM_MESSAGE = "message";

void led2_post_service (AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total);
void handleHome (AsyncWebServerRequest* request);
void post_send_message (AsyncWebServerRequest* request);
void led1_post_service (AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total);
void async_server_init (void);

void led2_post_service (AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
{
  // *** Code here is NOT executed *** 

  if ( request->contentType () == "application/json" )
  {
    //Serial.println ("Content type::"+request->contentType ());
    StaticJsonDocument<500> jsonConfig;

    String datos_JSON;
    for ( size_t i = 0; i < len; i++ )
    {
      //Serial.write (data[i]);
      datos_JSON += ( char ) data[i];
    }
    deserializeJson (jsonConfig, datos_JSON);
    boolean led = jsonConfig["GPIO2"];
    //Serial.println (led ? "true" : "false");
    digitalWrite (LED_2, led);
    log ("\n");
    log_info ("/led2-device");
    serializeJsonPretty (jsonConfig, Serial);
    request->send (200, "application/json", datos_JSON);
  }
  request->send (200, "application/json", "vacio");
}

void handleHome (AsyncWebServerRequest* request)
{
  AsyncResponseStream* response;

  File file = SPIFFS.open (F ("/index.html"), "r");
  if ( file )
  {
    file.setTimeout (100);
    String s = file.readString ();
    file.close ();

    s.replace (F ("#GPIO1_STATUS#"), digitalRead (LED_1) ? "ON" : "OFF");
    s.replace (F ("#GPIO2_STATUS#"), digitalRead (LED_2) ? "ON" : "OFF");
    s.replace (F ("#GPIO1_CLASE#"), digitalRead (LED_1) ? "button-on" : "button-off");
    s.replace (F ("#GPIO2_CLASE#"), digitalRead (LED_2) ? "button-on" : "button-off");
    s.replace (F ("#GPIO1#"), ( String ) ( LED_1 ));
    s.replace (F ("#GPIO2#"), ( String ) ( LED_2 ));

    // Send Data
    request->send (200, "text/html", s);
  }
  else
  {
    request->send (500, "text/plain", "/index.html not found, have you flashed the SPIFFS?");
  }
}

void post_send_message (AsyncWebServerRequest* request)
{
  String message;
  if ( request->hasParam (PARAM_MESSAGE, true) )
  {
    message = request->getParam (PARAM_MESSAGE, true)->value ();
  }
  else
  {
    message = "No message sent";
  }
  request->send (200, "text/plain", "Hello, POST: " + message);
}

void led1_post_service (AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
{
  // *** Code here is NOT executed *** 

  if ( request->contentType () == "application/json" )
  {
    //Serial.println ("Content type::"+request->contentType ());
    StaticJsonDocument<500> jsonConfig;

    String datos_JSON;
    for ( size_t i = 0; i < len; i++ )
    {
      //Serial.write (data[i]);
      datos_JSON += ( char ) data[i];
    }
    deserializeJson (jsonConfig, datos_JSON);
    boolean led = jsonConfig["GPIO1"];
    //Serial.println (led ? "true" : "false");
    digitalWrite (LED_1, led);
    log ("\n");
    log_info ("/led1-device");
    serializeJsonPretty (jsonConfig, Serial);
    request->send (200, "application/json", datos_JSON);
  }
  request->send (200, "application/json", "vacio");
}

void async_server_init (void)
{
  pinMode (LED_1, OUTPUT);
  pinMode (LED_2, OUTPUT);

  if ( !SPIFFS.begin (true) )
  {
    Serial.println ("An Error has occurred while mounting SPIFFS");
    return;
  }

  server.serveStatic ("/style.css", SPIFFS, "/style.css").setDefaultFile ("/style.css").setCacheControl ("max-age=600");
  server.serveStatic ("/index.js", SPIFFS, "/index.js").setDefaultFile ("/index.js").setCacheControl ("max-age=600");
  server.serveStatic ("/esp32.png", SPIFFS, "/esp32.png").setDefaultFile ("/esp32.png").setCacheControl ("max-age=600");

  // Route for root / web page
  server.on ("/", HTTP_GET, handleHome);
  server.on ("/led1-device", HTTP_POST, [] (AsyncWebServerRequest* request) {}, NULL, led1_post_service);
  server.on ("/led2-device", HTTP_POST, [] (AsyncWebServerRequest* request) {}, NULL, led2_post_service);
  server.on ("/post", HTTP_POST, post_send_message);

  server.begin ();
}

#endif // __DATA_ASYNC_H__