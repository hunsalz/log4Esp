#ifndef LOG4ESP_H
#define LOG4ESP_H

#ifndef ESP8266
#error “This library only supports boards with ESP8266 MCU.”
#endif

#include "Logger.h"
#include "Appender.h"
#include "RollingFileAppender.h"
#include "SerialAppender.h"

#endif // LOG4ESP_H
