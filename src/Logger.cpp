#include "Logger.h"

namespace log4arduino {

  Logger::Logger(const char* name, bool addDefaultSerialAppender) {
    
    _name = name;
    if (addDefaultSerialAppender) {
      _appender.push_back(getDefaultSerialAppender());
    }
  }

  String Logger::getName() {
    return _name;
  }

  std::vector<Appender>& Logger::getAppender() {
    return _appender;
  }

  void Logger::addFormatterToAll(Appender::FormatterFunction formatterFunction) {

    for (auto && fn : _appender) {
      fn.setFormatter(formatterFunction);
    }
  }

  void Logger::addFilterToAll(Appender::FilterFunction filterFunction) {

    for (auto && fn : _appender) {
      fn.addFilter(filterFunction);
    }
  }

  void Logger::addLevelToAll(Appender::Level level) {

    for (auto && fn : _appender) {
      fn.setLevel(level);
    }
  }

  void Logger::print(Appender::Level level, const char* msg, ...) {
    
    va_list args;
    va_start(args, msg);
    for (auto && fn : _appender) {
      fn.print(level, msg, &args);
    }
    va_end(args);
  }

  Appender Logger::getDefaultSerialAppender() {
    return SerialAppender(&Serial, true);
  }

  extern Logger LOG = Logger();
}