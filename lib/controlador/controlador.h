#ifndef __CONTROLADOR_H__
#define __CONTROLADOR_H__

#include <Arduino.h>

class Controlador
{
private:
    //* AP   
    char* _ap_name;
    char*  _ap_password;
    boolean _ap_access_point;
    boolean _ap_hidden;
    uint8_t _ap_canal;
    uint8_t _ap_connect;
    IPAddress _ap_local_ip;
    IPAddress _ap_gateway;
    IPAddress _ap_subnet;

    //* Station
    char* _sta_ssid;
    char* _sta_password;

public:
    Controlador ();
    ~Controlador ();
    //! ACCESS POINT FUNCTIONS
    void access_point_config (char* ap_name, char* ap_password, boolean ap_hidden, uint8_t ap_canal, uint8_t ap_connect);
    boolean access_point_start (void);
    void access_point_net_config (void);
    void print_access_point_creedentials (void);

    //! STATION MODE FUNTIONS
    void station_mode_config (char* sta_ssid, char* sta_password);
    boolean station_mode_start (void);
protected:
};
#endif // __CONTROLADOR_H__