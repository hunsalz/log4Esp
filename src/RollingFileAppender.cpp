#include "RollingFileAppender.h"

namespace log4arduino {

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

    _file = SPIFFS.open(getFileName(), "a+");

    // if (!_file && getFileName()) {
    //   // open existing file and set file preferences
    //   if (SPIFFS.exists(getFileName())) {
    //     _file = SPIFFS.open(getFileName(), "a+");
    //     if (_file) {
    //       Log.verbose(F("Open file [%s] successful." CR), getFileName().c_str());
    //       _offset = readOffset();
    //       _lineLength = readLineLength();
    //     } else {
    //       Log.error(F("Open file [%s] failed." CR), getFileName().c_str());
    //     }
    //   // create a new file and set default file preferences
    //   } else {
    //     _file = SPIFFS.open(getFileName(), "w+");
    //     if (_file) {
    //       Log.error(F("Creating new file [%s] successful." CR), getFileName().c_str());
    //       writeOffset(DEFAULT_OFFSET);
    //       _lineLength = 0; // unset by default
    //     } else {
    //       Log.error(F("Creating new file [%s] failed." CR), getFileName().c_str());
    //     }
    //   }
    // }

    return _file;
  }
}
