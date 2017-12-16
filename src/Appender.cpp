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

  Appender::Appender(Print* output) {
    _output = output;
  }

  Print& Appender::getOutput() {
    return *_output;
  }

  void Appender::setFormatter(FormatterFunction formatterFunction) {
    _formatterFunction = formatterFunction;
  }

  void Appender::print(Level level, char msg[], va_list *args) {

    if (_formatterFunction) {
      _formatterFunction(getOutput(), level, msg, args);
    } else {
      defaultFormatter(getOutput(), level, msg, args);
    }
  }

  void Appender::defaultFormatter(Print& output, Level level, char msg[], va_list *args) {
    
    output.print(F("["));
    output.print(Appender::toString(level));
    output.print(F("] "));
    size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
    char buffer[length];
    vsnprintf(buffer, length, msg, *args);
    output.print(buffer);
    output.println();
  }

  const __FlashStringHelper* Appender::toString(Appender::Level level) {

    switch (level) {
      case Appender::Level::NOTICE: return F("NOTICE"); break;
      case Appender::Level::WARNING: return F("WARNING"); break;
      case Appender::Level::ERROR: return F("ERROR"); break;
      case Appender::Level::FATAL: return F("FATAL"); break;
      case Appender::Level::SILENT: return F("SILENT"); break;
      default: return F("VERBOSE"); break;
    }
  }
}
