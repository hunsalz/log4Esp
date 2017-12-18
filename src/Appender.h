#ifndef APPENDER_H
#define APPENDER_H

#include <Arduino.h>
#include <inttypes.h>
#include <stdarg.h>

namespace log4arduino {

  class Appender {

    public:
      
      enum Level {
        FATAL = 0,
        ERROR = 1,
        WARNING = 2,
        NOTICE = 3,
        VERBOSE = 4
      };

      typedef std::function<void(Print& output, Level level, const char* msg, va_list *args)> FormatterFunction;

      typedef std::function<bool(Level level, const char* msg, va_list *args)> FilterFunction;

      Appender(Print* output, bool addDefaultFormatter = true);

      Print& getOutput();

      Appender::FormatterFunction getFormatter();

      void setFormatter(FormatterFunction formatterFunction);

      Appender::FilterFunction getFilter();

      void setFilter(FilterFunction filterFunction);

      void setLevel(Level level);

      void print(Level level, const char* msg, va_list *args);

      static Appender::FormatterFunction getDefaultFormatter();

      static const __FlashStringHelper* toString(Level level);

    private:

      Print* _output = NULL;
      FormatterFunction _formatterFunction = NULL;
      FilterFunction _filterFunction = NULL;
  };
}

#endif // APPENDER_H
