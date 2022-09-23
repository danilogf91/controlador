#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h> 
#include "controlador.h"
#include "log.h"

Controlador::Controlador (/* args */)
{
}

Controlador::~Controlador()
{
}

void Controlador::access_point_config (char* ap_name, char* ap_password, boolean ap_hidden, uint8_t ap_canal, uint8_t ap_connect)
{
    _ap_name = ap_name;
    _ap_password = ap_password;
    _ap_hidden = ap_hidden;
    _ap_canal = ap_canal;
    _ap_connect = ap_connect;
}

boolean Controlador::access_point_start(void)
{
    log_info ("Iniciando Modo AP");
    WiFi.disconnect ();
    WiFi.mode(WIFI_AP);
    delay (100);
    WiFi.softAP (_ap_name, _ap_password);
    this->access_point_net_config ();
    WiFi.softAPConfig (_ap_local_ip, _ap_gateway, _ap_subnet);
    IPAddress IP = WiFi.softAPIP ();
    log("AP IP address: ");
    Serial.println(IP);
    _ap_access_point = true;
    return _ap_access_point;
}

/// @brief Carga la IP por defecto para usar en el proyecto
/// @param void
void Controlador::access_point_net_config (void)
{
    IPAddress local_ip (192, 168, 5, 1);
    IPAddress gateway(192,168,5,1);
    IPAddress subnet (255, 255, 255, 0);
    _ap_local_ip = local_ip;
    _ap_gateway = gateway;
    _ap_subnet = subnet;
}

boolean Controlador::station_mode_start(void)
{
    log_info ("red WiFi->" + ( String ) _sta_ssid);
    log_info("pass WiFi->"+(String)_sta_password);
    log_info ("Iniciando Modo STA");
    //WiFi.disconnect ();
    WiFi.mode (WIFI_STA);
    WiFi.begin(_sta_ssid, _sta_password);
    log_info("Conectando a la red WiFi .....");

    while ( WiFi.status () != WL_CONNECTED )
    {
        log('.');
        delay(1000);
    }
    log_info("OK, Conectado a la red WiFi->"+(String)_sta_ssid);
    

    Serial.println (WiFi.localIP ());
    _ap_access_point = false;
    return _ap_access_point;
}

void Controlador::station_mode_config(char* sta_ssid, char* sta_password)
{
    _sta_ssid = sta_ssid;
    _sta_password = sta_password;
}

void Controlador::print_access_point_creedentials(void)
{
    log_info ("Access Point Name: " + (String)_ap_name);
    log_info ("Access Point Pass: " + (String)_ap_password);
}