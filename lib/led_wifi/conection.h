#ifndef __CONECTION_H__
#define __CONECTION_H__
#include <Arduino.h>

void create_task_led_wifi (void);
void task_connection_wifi_led (void* params);
void wifi_test_connection(void* params);



#endif // __CONECTION_H__