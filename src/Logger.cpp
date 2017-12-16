#include "Logger.h"

namespace log4arduino {

  Logger::Logger(): _appender(&Serial) {
  }

  String Logger::getName() {
    return _name;
  }

  Appender Logger::getAppender() {
    return _appender;
  }

  void Logger::setAppender(Appender appender) {
    _appender = appender;
  }

  Logger& Logger::getInstance() {
    
    static Logger logger;
    return logger;
  }
}