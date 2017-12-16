#ifndef APPENDER_H
#define APPENDER_H

#include <Arduino.h>
#include <inttypes.h>
#include <stdarg.h>

namespace log4arduino {

  class Appender {

    public:
      
      enum Level {
        VERBOSE = 0,
        NOTICE,
        WARNING,
        ERROR,
        FATAL,
        SILENT
      };

      typedef std::function<void(Print& output, Level level, char msg[], va_list *args)> FormatterFunction;

      Appender(Print* output);

      Print& getOutput();

      void setFormatter(FormatterFunction formatterFunction);

      void print(Level level, char msg[], va_list *args);

      static const __FlashStringHelper* toString(Level level);

    private:

      Print* _output = NULL;
      FormatterFunction _formatterFunction;

      void defaultFormatter(Print& output, Level level, char msg[], va_list *args);

      void printFormat(Print& output, const char format, va_list *args);
  };
}

#endif // APPENDER_H
