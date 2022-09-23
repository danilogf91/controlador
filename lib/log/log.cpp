#include "log.h"

#define DEBUG_SERIAL_PRINT Serial.println

void log_info (String data)
{
#ifdef DEBUG_SERIAL_PRINT
    DEBUG_SERIAL_PRINT ("Info: " + data);
#endif
}

void log_coments(String data)
{
#ifdef DEBUG_SERIAL_PRINT
    DEBUG_SERIAL_PRINT ("Comentarios: " + data);
#endif 
}

void log_error (String data)
{
#ifdef DEBUG_SERIAL_PRINT
    DEBUG_SERIAL_PRINT("Error: "+data);
#endif
}

void log_warning (String data)
{
#ifdef DEBUG_SERIAL_PRINT
    DEBUG_SERIAL_PRINT("Warning: "+data);
#endif
}

void log(String data)
{
#ifdef DEBUG_SERIAL_PRINT
    Serial.print(data);
#endif 
}