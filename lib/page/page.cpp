#include <Arduino.h>
#include "page.h"
#include "log.h"

Page::~Page()
{
    
}

Page::Page(uint8_t led1, uint8_t led2)
{
    _pin1_led = led1;
    _pin2_led = led2;
    bool _led1_status = false;
    bool _led2_status = false;
    pinMode (_pin1_led, OUTPUT);
    pinMode (_pin2_led, OUTPUT);
    digitalWrite (_pin1_led, LOW);
    digitalWrite (_pin1_led, LOW);
}


boolean Page::get_led_state(uint8_t led_pin)
{
    return ( led_pin == _pin1_led)? _led1_status :_led2_status;
}

void Page::set_led_state(uint8_t led_pin, boolean state)
{
    ( led_pin == _pin1_led ) ? digitalWrite(_pin1_led, state) : digitalWrite(_pin2_led, state);
    
    ( led_pin == _pin1_led ) ? _led1_status = state : _led2_status = state;
}

void Page::init()
{

    _servidor.stop ();
    _servidor.begin (_port);
}

