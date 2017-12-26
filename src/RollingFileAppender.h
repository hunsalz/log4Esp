#ifndef ROLLING_FILE_APPENDER_H
#define ROLLING_FILE_APPENDER_H

#include <FS.h> // https://github.com/esp8266/Arduino/tree/master/cores/esp8266/FS.h

#include "Appender.h"

namespace log4arduino {

  class RollingFileAppender: public Appender {

    public:

      RollingFileAppender(const char* fileName, bool addDefaultFormatter = true);

      Print& getOutput();

      const char* getFileName();

      File getFile();

    private:

      const char* _fileName = NULL;
      File _file;
  };
}

#endif // ROLLING_FILE_APPENDER_H
