#ifndef ROLLING_FILE_APPENDER_H
#define ROLLING_FILE_APPENDER_H

#if defined(ESP32)
#include <SPIFFS.h>
#else
#include <FS.h>
#endif

#include "Appender.h"
#include "Logger.h"

namespace log4Esp {

/**
 * RollingFileAppender logs data to a rolling file.
 */
class RollingFileAppender : public Appender {

public:
  RollingFileAppender(const char *fileName, uint16_t maxRowLength = 128, uint16_t maxRows = 512,
                      bool addDefaultFormatter = true);

  Print &getOutput();

  /**
   * \return file name
   */
  const char *getFileName();

  /**
   * \return max row length
   */
  uint16_t getMaxRowLength();

  /**
   * \return max number of rows before logging starts from beginning again
   */
  uint16_t getMaxRows();

protected:
  void begin(Level level, const char *msg, va_list *args);

  void end(Level level, const char *msg, va_list *args);

private:
  const char *_fileName = NULL;
  File _file;
  uint16_t _lastOffset;
  uint16_t _maxRowLength;
  uint16_t _maxRows;
  Logger _log = Logger();

  const static int OFFSET_LENGTH = 11; // 10 digits to keep an full integer value and 1 digit for CR

  /**
   * \return offset of an existing log file
   */
  uint16_t readOffset();

  /**
   * \param write offset into an existing log file
   */
  void writeOffset(uint16_t offset);

  /**
   * \return max row length of an existing log file
   */
  uint16_t readMaxRowLength();

  /**
   * \return file instance
   */
  File getFile();
};
} // namespace log4Esp

#endif // ROLLING_FILE_APPENDER_H
