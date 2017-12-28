#include "RollingFileAppender.h"

namespace log4arduino {

  RollingFileAppender::RollingFileAppender(const char* fileName, uint16_t maxRowLength, uint16_t maxRows, bool addDefaultFormatter) {
    
    _fileName = fileName;
    _maxRowLength = maxRowLength;
    _maxRows = maxRows;

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

  uint16_t RollingFileAppender::getMaxRowLength() {

    getFile(); // assure that file is initialized first
    return _maxRowLength;
  }

  uint16_t RollingFileAppender::getMaxRows() { 
    return _maxRows;
  }

  void RollingFileAppender::begin(Level level, const char* msg, va_list *args) {
    _lastOffset = getFile().position();
  }

  void RollingFileAppender::end(Level level, const char* msg, va_list *args) {

    int diff = getFile().position() - _lastOffset;

    // define spacing = maxRowLength - written characters between last and current offset
    int spacing = getMaxRowLength() - (getFile().position() - _lastOffset);
    // if spacing is greater zero then fill up the line with spaces
    if (spacing > 0) {
      Serial.printf("TAB %d + %d = 32\n", spacing, diff);

      getOutput().printf("%*s", spacing, "");
    }
    // if spacing is less zero then turn around cursor to maxRowLength
    if (spacing < 0) {
      Serial.printf("REDUCE %d + %d = 32\n", spacing, diff);
      
      // grap 4 charactors extra to add [..] at the end
      getFile().seek((spacing - 4), SeekCur);
      getOutput().print(F("[..]"));
    }
  
    // finalize log row automatically with CR
    getOutput().println();

    // save current cursor position
    uint16_t offset = getFile().position();
    // check if rollover is imminent
    if (offset >= (32 * 10)) {
      offset = OFFSET_LENGTH + 1;

      Serial.println("ROLLOVER");
    }
    // persist new offset position in file
    writeOffset(offset);
    // turn back to last cursor position
    getFile().seek(offset, SeekSet);
  }

  uint16_t RollingFileAppender::readOffset() {

    uint16_t offset = OFFSET_LENGTH + 1; // assume first log row position as fallback solution
    File file = getFile();
    if (file) {
      file.seek(0, SeekSet);
      String line = file.readStringUntil('\n');
      offset = line.toInt();
      if (offset == 0) {
        //LOG.error(F("File [%s] doesn't contain a valid offset value."), getPath().c_str());
      }
    }

    return offset;
  }

  void RollingFileAppender::writeOffset(uint16_t offset) {

    File file = getFile();
    if (file) {
      file.seek(0, SeekSet);
      char digits[10]; // max offset value consists of 10 digits
      sprintf(digits, "%-10d", offset);
      file.print(digits);
      file.flush();
    }
  }

  uint16_t RollingFileAppender::readMaxRowLength() {

    uint16_t maxLength = 0;
    File file = getFile();
    if (file) {
      file.seek(OFFSET_LENGTH, SeekSet);
      String line = file.readStringUntil('\n');
      maxLength = line.length();
    }

    return maxLength;
  }

  File RollingFileAppender::getFile() {

    if (!_file && getFileName()) {
      // open existing file and set file preferences
      if (SPIFFS.exists(getFileName())) {
        _file = SPIFFS.open(getFileName(), "r+");
        if (_file) {
          //LOG.verbose(F("Open file [%s] successful."), getFileName().c_str());
          _file.seek(readOffset(), SeekSet);
          _maxRowLength = readMaxRowLength();
        } else {
          //LOG.error(F("Open file [%s] failed."), getFileName().c_str());
        }
      // create a new file and set default file preferences
      } else {
        _file = SPIFFS.open(getFileName(), "w+");
        if (_file) {
          //LOG.error(F("Creating new file [%s] successful."), getFileName().c_str());
          writeOffset(OFFSET_LENGTH);
          _file.println(); // move cursor to first log row position
        } else {
          //LOG.error(F("Creating new file [%s] failed."), getFileName().c_str());
        }
      }
    }

    return _file;
  }
}
