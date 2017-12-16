#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <inttypes.h>
#include <stdarg.h>

#include "Appender.h"

namespace log4arduino {

  class Logger {

    public:

      void notice(char msg[], ...) {
        
        va_list args;
        va_start(args, msg);
        _appender.print(Appender::NOTICE, msg, &args);

        va_end(args);
      }

      String getName();

      Appender getAppender();

      void setAppender(Appender appender);

      static Logger& getInstance();

    private:

      Logger();
      Logger(const Logger&);
      void operator = (const Logger&);

      Appender _appender;

      const char* _name = "MyLogger";
  };
}

#endif // LOGGER_H
