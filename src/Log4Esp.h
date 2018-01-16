#ifndef LOG4ESP_H
#define LOG4ESP_H

#ifndef ESP8266
#error “This library only supports boards with ESP8266 MCU.”
#endif

#include "appender/Appender.h"
#include "appender/RollingFileAppender.h"
#include "appender/SerialAppender.h"
#include "Logger.h"

#endif // LOG4ESP_H
