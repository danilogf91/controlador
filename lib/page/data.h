#include "page.h"
#include "log.h"

#define LED_1 2
#define LED_2 25

#define PORT 81
Page simple_web_server (LED_1, LED_2);

void handle_OnConnect ();
void handle_led1on (void);
void handle_led1off (void);
void handle_led2on (void);
void handle_led2off (void);
void handle_NotFound (void);
String SendHTML ();
void simple_server_init (void);
void simple_server_loop (void);

void handle_OnConnect ()
{
  log_info ("Leer GPIO"+(String)LED_1 +" Status: | Leer GPIO"+(String)LED_2+" Status:");
  simple_web_server.send(200, "text/html", SendHTML()); 
}

void handle_led1on() {
  simple_web_server.set_led_state (LED_1, HIGH);
  log_info ("GPIO"+(String)LED_1 +" Status: ON");
  simple_web_server.send(200, "text/html", SendHTML()); 
}

void handle_led1off() {
  simple_web_server.set_led_state (LED_1, LOW);
  log_info ("GPIO"+(String)LED_1 +" Status: OFF");
  simple_web_server.send(200, "text/html", SendHTML()); 
}

void handle_led2on() {
  simple_web_server.set_led_state (LED_2, HIGH);
  log_info ("GPIO"+(String)LED_2 +" Status: ON");
  simple_web_server.send(200, "text/html", SendHTML()); 
}

void handle_led2off() {
  simple_web_server.set_led_state (LED_2, LOW);
  log_info ("GPIO"+(String)LED_2 +" Status: OFF");
  simple_web_server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound(){
  simple_web_server.send(404, "text/plain", "Not found test");
}

String SendHTML ()
{
    String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web simple_web_server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(simple_web_server.get_led_state(LED_1))
  {ptr +="<p>GPIO"+(String)LED_1 +" Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>GPIO"+(String)LED_1 +" Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(simple_web_server.get_led_state(LED_2))
  {ptr +="<p>GPIO"+(String)LED_2 +" Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>GPIO"+(String)LED_2 +" Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void simple_server_init (void)
{
    log_coments ("Cargando paginas...");
    simple_web_server.on ("/", handle_OnConnect);
    simple_web_server.on("/led1on", handle_led1on);
    simple_web_server.on("/led1off", handle_led1off);
    simple_web_server.on("/led2on", handle_led2on);
    simple_web_server.on("/led2off", handle_led2off);
    simple_web_server.onNotFound (handle_NotFound);
    log_coments ("Paginas cargadas OK");
    simple_web_server.begin (PORT);
    log_info ("HTTP server started");
}

void simple_server_loop (void)
{
        simple_web_server.handleClient();
}