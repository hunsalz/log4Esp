#include "RollingFileAppender.h"

namespace log4Esp {

RollingFileAppender::RollingFileAppender(const char *fileName, uint16_t maxRowLength, uint16_t maxRows,
                                         bool addDefaultFormatter) {
  _fileName = fileName;
  _maxRowLength = maxRowLength;
  _maxRows = maxRows;

  if (addDefaultFormatter) {
    setFormatter(Appender::getDefaultFormatter());
  }
  // load SPIFFS by default
  if (SPIFFS.begin()) {
    _log.verbose(F("File system mounted."));
  } else {
    _log.warning(F("Mounting file system failed."));
  }
}

Print &RollingFileAppender::getOutput() { return _file; }

const char *RollingFileAppender::getFileName() { return _fileName; }

uint16_t RollingFileAppender::getMaxRowLength() {

  getFile(); // assure that file is initialized first
  return _maxRowLength;
}

uint16_t RollingFileAppender::getMaxRows() { return _maxRows; }

void RollingFileAppender::begin(Level level, const char *msg, va_list *args) { _lastOffset = getFile().position(); }

void RollingFileAppender::end(Level level, const char *msg, va_list *args) {

  // spacing = maxRowLength - written characters between last and current offset - CR
  int spacing = getMaxRowLength() - (getFile().position() - _lastOffset) - 1;
  // if spacing is greater zero then fill up the line with spaces
  if (spacing > 0) {
    getOutput().printf("%*s", spacing, "");
  }
  // if spacing is less zero then turn around cursor to maxRowLength
  if (spacing < 0) {
    // grap 4 charactors extra to add [..] at the end
    getFile().seek((spacing - 4), SeekCur);
    getOutput().print(F("[..]"));
  }
  // finalize log row automatically with CR
  getOutput().println();
  // save current cursor position
  uint16_t offset = getFile().position();
  // check if rollover is imminent
  if (offset >= (getMaxRowLength() * getMaxRows())) {
    // move cursor to first log row position
    offset = OFFSET_LENGTH + 1;
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
      _log.error(F("Log file [%s] doesn't contain a valid offset value."), getFileName());
    }
  }

  return offset;
}

void RollingFileAppender::writeOffset(uint16_t offset) {

  File file = getFile();
  if (file) {
    file.seek(0, SeekSet);
    char digits[11]; // max offset value consists of 10 digits
    sprintf(digits, "%-10d", offset);
    file.print(digits);
    file.flush();
  }
}

uint16_t RollingFileAppender::readMaxRowLength() {

  uint16_t maxRowLength = 0;
  File file = getFile();
  if (file) {
    // move cursor to first log row position
    file.seek(OFFSET_LENGTH + 1, SeekSet);
    // read first line and take value as maxRowLength
    maxRowLength = file.readStringUntil('\n').length();
  }

  return maxRowLength;
}

File RollingFileAppender::getFile() {

  if (!_file && getFileName()) {
    // open existing file and set file preferences
    if (SPIFFS.exists(getFileName())) {
      _file = SPIFFS.open(getFileName(), "r+");
      if (_file) {
        _log.trace(F("Open log file [%s] successful."), getFileName());
        _file.seek(readOffset(), SeekSet);
        _maxRowLength = readMaxRowLength();
      } else {
        _log.error(F("Open log file [%s] failed."), getFileName());
      }
      // create a new file and set default file preferences
    } else {
      _file = SPIFFS.open(getFileName(), "w+");
      if (_file) {
        _log.trace(F("Creating new log file [%s] was successful."), getFileName());
        writeOffset(OFFSET_LENGTH);
        _file.println(); // move cursor to first log row position
      } else {
        _log.error(F("Creating new log file [%s] failed."), getFileName());
      }
    }
  }

  return _file;
}
} // namespace log4Esp
