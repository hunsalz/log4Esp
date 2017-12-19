#include "SerialAppender.h"

namespace log4arduino {

  SerialAppender::SerialAppender(Print* output, bool addDefaultFormatter) {
    
    setOutput(output);
    if (addDefaultFormatter) {
      setFormatter(Appender::getDefaultFormatter());
    }
  }
}
