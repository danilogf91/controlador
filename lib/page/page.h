#ifndef __PAGE_H__
#define __PAGE_H__
#include <Arduino.h>
#include <WebServer.h>

class Page: public WebServer
{
private:
    uint8_t _pin1_led;
    uint8_t _pin2_led;
    uint16_t _port;
    bool _led1_status;
    bool _led2_status;
    WebServer _servidor;


    public:
    Page (uint8_t led1, uint8_t led2);
    boolean get_led_state (uint8_t led_pin);
    void set_led_state (uint8_t led_pin, boolean state);
    void init ();
    ~Page ();

protected:
};


#endif // __PAGE_H__