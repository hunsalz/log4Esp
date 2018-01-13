#include "SerialAppender.h"

namespace log4Esp {

SerialAppender::SerialAppender(bool addDefaultFormatter) {
  if (addDefaultFormatter) {
    setFormatter(Appender::getDefaultFormatter());
  }
}

Print &SerialAppender::getOutput() { return Serial; }

void SerialAppender::begin(Level level, const char *msg, va_list *args) {}

void SerialAppender::end(Level level, const char *msg, va_list *args) {
  // finalize log row automatically with CR
  getOutput().println();
}
} // namespace log4Esp
