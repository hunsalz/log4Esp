#ifndef LOGGER_H
#define LOGGER_H

#ifdef Arduino_h
// arduino is not compatible with std::vector
#undef min
#undef max
#endif
#include <vector>

#include <inttypes.h>
#include <stdarg.h>

#include "Appender.h"

namespace log4arduino {

  class Logger {

    public:

      Logger(const char* name = "default", bool addDefaultSerialAppender = true);

      void notice(const char* msg, ...) {
        
        va_list args;
        va_start(args, msg);
        // TODO remove debug output
        // Serial.print("### ");
        // Serial.print(getName());
        // Serial.println(" ### ");
        print(Appender::NOTICE, msg, &args);
        va_end(args);
      }

      String getName();

      std::vector<Appender>& getAppender();

      void addFormatterToAll(Appender::FormatterFunction formatterFunction);

      void addFilterToAll(Appender::FilterFunction filterFunction);

      void addLevelToAll(Appender::Level level);

      void print(Appender::Level level, const char* msg, va_list *args);

      static Appender getDefaultSerialAppender();

    private:

      const char* _name;

      std::vector<Appender> _appender;
  };

  extern Logger LOG;
}

#endif // LOGGER_H
