#include "conection.h"
#include <WiFi.h>
#include "log.h"


boolean wifi_conected = false;
static TaskHandle_t receiverHandler = NULL;

void task_connection_wifi_led (void* params)
{
    uint8_t led_wifi = 25;
    pinMode (led_wifi, OUTPUT);
    uint16_t min = 1, max = 150, number = 1;

    boolean conectado = *((boolean*)params);

    while ( true )
    {
        number = random (min, max);
        if ( true )
        {
            log_info ("WIFI conectado OK " + ( String ) conectado);
            digitalWrite (led_wifi, !digitalRead (led_wifi));
            vTaskDelay (number / portTICK_PERIOD_MS);
        }
        else
        {
            //log_info ("WiFi desconectado");
            // digitalWrite (led_wifi, !digitalRead(led_wifi));
            // vTaskDelay (500 / portTICK_PERIOD_MS);
            // digitalWrite (led_wifi, !digitalRead(led_wifi));
            // vTaskDelay (1000 / portTICK_PERIOD_MS);
            // digitalWrite (led_wifi, !digitalRead(led_wifi));
            // vTaskDelay (1500 / portTICK_PERIOD_MS);
            digitalWrite (led_wifi, !digitalRead (led_wifi));
            vTaskDelay (2000 / portTICK_PERIOD_MS);
        }
    }
}

void wifi_test_connection (void* params)
{
    while ( true )
    {
        if ( WL_CONNECTED == WiFi.status () )
        {
            log_info ("WIFI conectado OK ");
            wifi_conected = true;
            vTaskDelay (10000 / portTICK_PERIOD_MS);
        }
        else
        {
            log_info ("WiFi desconectado"); // TODO Reconectar wifi / crear ap y seguir trabajando
            wifi_conected = false;
            vTaskDelay (10000 / portTICK_PERIOD_MS);
        }
    }
}

void create_task_led_wifi (void)
{
    xTaskCreate (task_connection_wifi_led, "led_wifi", 2048, &wifi_conected, 1, NULL);
    xTaskCreate (wifi_test_connection, "wifi_test", 2048, NULL, 1, NULL);
}
