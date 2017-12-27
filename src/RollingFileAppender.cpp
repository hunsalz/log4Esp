#include "RollingFileAppender.h"

namespace log4arduino {

  // TODO add rolling file functionality

  RollingFileAppender::RollingFileAppender(const char* fileName, bool addDefaultFormatter) {
    
    _fileName = fileName;

    getFile();

    if (addDefaultFormatter) {
      setFormatter(Appender::getDefaultFormatter());
    }
  }

  Print& RollingFileAppender::getOutput() {
    return _file;
  }

  const char* RollingFileAppender::getFileName() {
    return _fileName;
  }

  File RollingFileAppender::getFile() {

    if (!_file && getFileName()) {
      // open existing file and set file preferences
      if (SPIFFS.exists(getFileName())) {
        _file = SPIFFS.open(getFileName(), "a+");
      // create a new file and set default file preferences
      } else {
        _file = SPIFFS.open(getFileName(), "w+"); 
      }
    }
    return _file;
  }
}
