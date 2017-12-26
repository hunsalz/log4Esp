#include "SerialAppender.h"

namespace log4arduino {

  SerialAppender::SerialAppender(bool addDefaultFormatter) {
    
    if (addDefaultFormatter) {
      setFormatter(Appender::getDefaultFormatter());
    }
  }

  Print& SerialAppender::getOutput() {
    return Serial;
  }
}
