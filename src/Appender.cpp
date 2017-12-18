#include "Appender.h"

namespace log4arduino {

  // const char LEVEL_VERBOSE[] PROGMEM = "VERBOSE";
  // const char LEVEL_NOTICE[] PROGMEM = "NOTICE";
  // const char LEVEL_WARNING[] PROGMEM = "WARNING";
  // const char LEVEL_ERROR[] PROGMEM = "ERROR";
  // const char LEVEL_FATAL[] PROGMEM = "FATAL";
  // const char LEVEL_SILENT[] PROGMEM = "SILENT";

  // const char* const LOG_LEVEL_STRINGS[] PROGMEM = {
  //   LEVEL_VERBOSE,
  //   LEVEL_NOTICE,
  //   LEVEL_WARNING,
  //   LEVEL_ERROR,
  //   LEVEL_FATAL,
  //   LEVEL_SILENT
  // };

  Appender::Appender(Print* output, bool addDefaultFormatter) {
    
    _output = output;
    if (addDefaultFormatter) {
      setFormatter(Appender::getDefaultFormatter());
    }
  }

  Print& Appender::getOutput() {
    return *_output;
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
      for (auto && fn : _filterFunctions) {
        filter = fn(level, msg, args);
        if (filter) break;
      }
      if (!filter) {
        _formatterFunction(getOutput(), level, msg, args);
      } else {
        // TODO: remove debug output
        Serial.println("FILTER OUTPUT !!!");
      }
    }
  }

  Appender::FormatterFunction Appender::getDefaultFormatter() {
        
    return  [](Print& output, Appender::Level level, const char* msg, va_list *args) {

      output.print(F("["));
      output.print(Appender::toString(level));
      output.print(F("] "));
      size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
      char buffer[length];
      vsnprintf(buffer, length, msg, *args);
      output.print(buffer);
      output.println();
    };
  }

  const __FlashStringHelper* Appender::toString(Appender::Level level) {

    switch (level) {
      case Appender::Level::FATAL: return F("FATAL"); break;
      case Appender::Level::ERROR: return F("ERROR"); break;
      case Appender::Level::WARNING: return F("WARNING"); break;
      case Appender::Level::NOTICE: return F("NOTICE"); break;
      default: return F("VERBOSE"); break;
    }
  }
}