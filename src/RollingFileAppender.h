#ifndef ROLLING_FILE_APPENDER_H
#define ROLLING_FILE_APPENDER_H

#include <FS.h> // https://github.com/esp8266/Arduino/tree/master/cores/esp8266/FS.h

#include "Appender.h"

namespace log4arduino {

  class RollingFileAppender: public Appender {

    public:

      RollingFileAppender(const char* fileName, uint16_t maxRowLength = 128, uint16_t maxRows = 512, bool addDefaultFormatter = true);

      /*
       * Return log output.
       */
      Print& getOutput();

      /*
       Return file name.
       */
      const char* getFileName();

      /*
        
       */
      uint16_t getMaxRowLength();

      /*
       
       */
      uint16_t getMaxRows();

    protected:

      void begin(Level level, const char* msg, va_list *args);

      void end(Level level, const char* msg, va_list *args);

    private:

      const char* _fileName = NULL;
      File _file;
      uint16_t _lastOffset;
      uint16_t _maxRowLength;
      uint16_t _maxRows;

      const static int OFFSET_LENGTH = 11; // 10 digits and CR as default value

      uint16_t readOffset();

      void writeOffset(uint16_t offset);

      uint16_t readMaxRowLength();

      /*
       Return file instance.
       */
      File getFile();
  };
}

#endif // ROLLING_FILE_APPENDER_H
