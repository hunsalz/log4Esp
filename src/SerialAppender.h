#ifndef SERIAL_APPENDER_H
#define SERIAL_APPENDER_H

#include "Appender.h"

namespace log4arduino {

  class SerialAppender: public Appender {

    public:

      SerialAppender(bool addDefaultFormatter = true);

      Print& getOutput();
  };
}

#endif // SERIAL_APPENDER_H
