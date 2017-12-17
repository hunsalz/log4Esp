#ifndef LOGGER_H
#define LOGGER_H

#ifdef Arduino_h
// arduino is not compatible with std::vector
#undef min
#undef max
#endif
#include <vector>

#include <Arduino.h>
#include <inttypes.h>
#include <stdarg.h>

#include "Appender.h"

namespace log4arduino {

  class Logger {

    public:

      Logger(const char* name);

      void notice(char msg[], ...) {
        
        va_list args;
        va_start(args, msg);
        // Serial.print("### ");
        // Serial.print(getName());
        // Serial.println(" ### ");
        print(Appender::NOTICE, msg, &args);
        va_end(args);
      }

      String getName();

      Appender get(uint16_t index);

      void add(Appender appender);

    private:

      std::vector<Appender> _appender;

      const char* _name;

      void print(Appender::Level level, char msg[], va_list *args);
  };

  extern Logger LOG;
}

#endif // LOGGER_H
