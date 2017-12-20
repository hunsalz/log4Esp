#include "Appender.h"

namespace log4arduino {

  const char LEVEL_FATAL[] PROGMEM = "FATAL";
  const char LEVEL_ERROR[] PROGMEM = "ERROR";
  const char LEVEL_WARNING[] PROGMEM = "WARNING";
  const char LEVEL_VERBOSE[] PROGMEM = "VERBOSE";
  const char LEVEL_NOTICE[] PROGMEM = "TRACE";

  const char* const LOG_LEVEL_STRINGS[] PROGMEM = {
    LEVEL_VERBOSE,
    LEVEL_NOTICE,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_FATAL
  };

  Print& Appender::getOutput() {
    return *_output;
  }

  void Appender::setOutput(Print* output) {
    _output = output;
  }

  Appender::FormatterFunction Appender::getFormatter() {
    return _formatterFunction;
  }

  void Appender::setFormatter(FormatterFunction formatterFunction) {
    _formatterFunction = formatterFunction;
  }

  std::vector<Appender::FilterFunction>& Appender::getFilter() {
    return _filterFunctions;
  }

  void Appender::addFilter(FilterFunction filterFunction) {
    _filterFunctions.push_back(filterFunction);
  }

  void Appender::setLevel(Level level) {

    addFilter([level](Appender::Level _level, const char* msg, va_list *args) -> bool {
      
      if (_level <= level) {
        return false;
      } else {
        return true;
      }
    });
  }

  void Appender::print(Level level, const char* msg, va_list *args) {

    if (getFormatter()) {
      bool filter = false;
      for (auto && fn : getFilter()) {
        filter = fn(level, msg, args);
        if (filter) break;
      }
      if (!filter) {
        _formatterFunction(getOutput(), level, msg, args);
      }
    }
  }

  Appender::FormatterFunction Appender::getDefaultFormatter() {
        
    return  [](Print& output, Appender::Level level, const char* msg, va_list *args) {

      output.print(F("["));
      output.print(Appender::toString(level, true));
      output.print(F("] "));
      size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
      char buffer[length];
      vsnprintf(buffer, length, msg, *args);
      output.print(buffer);
      output.println();
    };
  }

  const __FlashStringHelper* Appender::toString(Appender::Level level, bool shortName) {

    switch (level) {
      case Appender::Level::FATAL: return shortName ? F("F") : F("FATAL"); break;
      case Appender::Level::ERROR: return shortName ? F("E") : F("ERROR"); break;
      case Appender::Level::WARNING: return shortName ? F("W") : F("WARNING"); break;
      case Appender::Level::VERBOSE: return shortName ? F("V") : F("VERBOSE"); break;
      default: return shortName ? F("T") : F("TRACE"); break;
    }
  }
}