// Arduino Libraries
#include <Arduino.h>

// Own libraries
#include "controlador.h"
#include "log.h"
#include "data.h"
#include "page.h"

Controlador esp;

#define BAUDIOS 115200

void setup ()
{
  Serial.begin (BAUDIOS);
  log_coments ("");
  log_coments ("Inicializar puerto Serial a " + ( String ) BAUDIOS + " Baudios");
  esp.access_point_config ((char*)"esp32_admin", (char*)"esp32_password", false, 9, 4);
  log_coments ("Inicia configuracion credenciales para la red WIFI");

  //esp.access_point_start ();
  //log_coments ("Crea la red WIFI, con las credenciales por defecto");

  //esp.print_access_point_creedentials ();
  //log_coments ("Imprime las credenciales del Access Point");

  esp.station_mode_config ((char*)"hPalmiraCM", (char*)"Hpalmira17");
  log_coments ("Inicializa el modo Station del equipo");
  
  esp.station_mode_start ();
  log_coments ("Arranca la conexion a la red WiFi en modo STA");

  simple_server_init ();
}

void loop() {
  simple_server_loop ();
}

