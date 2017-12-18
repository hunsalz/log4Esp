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

  void Logger::setFormatterToAll(Appender::FormatterFunction formatterFunction) {

    for (std::vector<Appender>::iterator i = _appender.begin(); i != _appender.end(); ++i) {
      i->setFormatter(formatterFunction);
    }
  }

  void Logger::setLevelToAll(Appender::Level level) {

    for (std::vector<Appender>::iterator i = _appender.begin(); i != _appender.end(); ++i) {
      i->setLevel(level);
    }
  }

  void Logger::print(Appender::Level level, char msg[], va_list *args) {
    
    for (std::vector<Appender>::iterator i = _appender.begin(); i != _appender.end(); ++i) {
      i->print(level, msg, args);
    }
  }

  Appender Logger::getDefaultSerialAppender() {
    return Appender(&Serial, true);
  }

  extern Logger LOG = Logger();
}