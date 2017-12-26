#ifndef APPENDER_H
#define APPENDER_H

#ifdef Arduino_h
// arduino is not compatible with std::vector
#undef min
#undef max
#endif
#include <vector>

#include <Arduino.h>

namespace log4arduino {

  class Appender {

    public:
      
      enum Level {
        FATAL = 0,
        ERROR = 1,
        WARNING = 2,
        VERBOSE = 3,
        TRACE = 4
      };

      typedef std::function<void(Print& output, Level level, const char* msg, va_list *args)> FormatterFunction;

      typedef std::function<bool(Level level, const char* msg, va_list *args)> FilterFunction;

      virtual Print& getOutput() = 0;

      Appender::FormatterFunction getFormatter();

      void setFormatter(FormatterFunction formatterFunction);

      std::vector<Appender::FilterFunction>& getFilter();

      void addFilter(FilterFunction filterFunction);

      void setLevel(Level level);

      void print(Level level, const char* msg, va_list *args);
      
      static Appender::FormatterFunction getDefaultFormatter();

      static const __FlashStringHelper* toString(Level level, bool shortName = true);

    private:

      FormatterFunction _formatterFunction = NULL;

      std::vector<FilterFunction> _filterFunctions;
  };
}

#endif // APPENDER_H
