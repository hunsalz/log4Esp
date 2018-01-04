#include "Logger.h"

namespace log4Esp {

  Logger::Logger(const char* name, bool addDefaultSerialAppender) {
    
    _name = name;
    if (addDefaultSerialAppender) {
      getAppender().push_back(new SerialAppender(true));
    }
  }

  const char* Logger::getName() {
    return _name;
  }

  std::vector<Appender*>& Logger::getAppender() {
    return _appender;
  }

  void Logger::addFormatterToAll(Appender::FormatterFunction formatterFunction) {

    for (auto && fn : getAppender()) {
      fn->setFormatter(formatterFunction);
    }
  }

  void Logger::addFilterToAll(Appender::FilterFunction filterFunction) {

    for (auto && fn : getAppender()) {
      fn->addFilter(filterFunction);
    }
  }

  void Logger::addLevelToAll(Appender::Level level) {

    for (auto && fn : getAppender()) {
      fn->setLevel(level);
    }
  }

  extern Logger LOG = Logger();
}