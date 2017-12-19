#ifndef SERIAL_APPENDER_H
#define SERIAL_APPENDER_H

#include "Appender.h"

namespace log4arduino {

  class SerialAppender: public Appender {

    public:

      SerialAppender(Print* output, bool addDefaultFormatter = true);
  };
}

#endif // SERIAL_APPENDER_H
