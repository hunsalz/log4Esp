#ifndef SERIAL_APPENDER_H
#define SERIAL_APPENDER_H

#include "Appender.h"

namespace log4Esp {

/**
 * SerialAppender logs data to Serial.
 */
class SerialAppender : public Appender {

public:
  SerialAppender(bool addDefaultFormatter = true);

  Print &getOutput();

protected:
  void begin(Level level, const char *msg, va_list *args);

  void end(Level level, const char *msg, va_list *args);
};
} // namespace log4Esp

#endif // SERIAL_APPENDER_H
