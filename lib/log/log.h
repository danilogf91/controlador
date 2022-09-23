#ifndef __LOG_H__
#define __LOG_H__
#include <Arduino.h>

void log_info (String data);
void log_coments (String data);
void log_error (String data);
void log_warnig (String data);
void log (String data);

#endif // __LOG_H__
