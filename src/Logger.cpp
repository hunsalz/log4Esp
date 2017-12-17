#include "Logger.h"

namespace log4arduino {

  Logger::Logger(const char* name) {
    _name = name;
  }

  String Logger::getName() {
    return _name;
  }

  Appender Logger::get(uint16_t index) {
    return _appender.at(index);
  }

  void Logger::add(Appender appender) {
    _appender.push_back(appender);
  }

  void Logger::print(Appender::Level level, char msg[], va_list *args) {
    
    if (_appender.empty()) {
      Appender appender = Appender(&Serial);
      appender.setFormatter([](Print& output, Appender::Level level, const char* msg, va_list *args) {
        
        output.print(Appender::toString(level));
        output.print(F("] "));
        size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
        char buffer[length];
        vsnprintf(buffer, length, msg, *args);
        output.print(buffer);
        output.println();
      });
      add(appender);
    }
    for (std::vector<Appender>::iterator i = _appender.begin(); i != _appender.end(); ++i) {
        
      i->print(level, msg, args);
        
    }
  }

  extern Logger LOG = Logger("default");
}