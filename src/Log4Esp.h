#ifndef LOG4ESP_H
#define LOG4ESP_H

#include "appender/Appender.h"
#include "appender/RollingFileAppender.h"
#include "appender/SerialAppender.h"
#include "Logger.h"

#ifndef LOGGER_NO_GLOBALS
using log4Esp::Appender;
using log4Esp::RollingFileAppender;
using log4Esp::SerialAppender;
using log4Esp::Logger;
#endif // LOGGER_NO_GLOBALS

#endif // LOG4ESP_H
