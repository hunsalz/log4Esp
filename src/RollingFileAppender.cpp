#include "RollingFileAppender.h"

namespace log4arduino {

  RollingFileAppender::RollingFileAppender(const char* path, bool addDefaultFormatter) {
    
    File file = getFile();
    setOutput(&file);
     
    if (addDefaultFormatter) {
      setFormatter(Appender::getDefaultFormatter());
    }
  }

  const char* RollingFileAppender::getPath() {
    return _path;
  }

  File RollingFileAppender::getFile() {

    if (!_file && getPath()) {
      // open existing file and set file preferences
      if (SPIFFS.exists(getPath())) {
        _file = SPIFFS.open(getPath(), "r+");
        if (_file) {
          //Log.verbose(F("Open file [%s] successful." CR), getPath().c_str());
          //_offset = readOffset();
          //_lineLength = readLineLength();
        } else {
          //Log.error(F("Open file [%s] failed." CR), getPath().c_str());
        }
      // create a new file and set default file preferences
      } else {
        _file = SPIFFS.open(getPath(), "w+");
        if (_file) {
          //Log.error(F("Creating new file [%s] successful." CR), getPath().c_str());
          //writeOffset(DEFAULT_OFFSET);
          //_lineLength = 0; // unset by default
        } else {
          //Log.error(F("Creating new file [%s] failed." CR), getPath().c_str());
        }
      }
    }
  }
}
