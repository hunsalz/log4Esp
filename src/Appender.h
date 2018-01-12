#ifndef APPENDER_H
#define APPENDER_H

#ifdef Arduino_h
// Arduino is not compatible with std::vector
#undef min
#undef max
#endif
#include <vector>

#include <Arduino.h>

namespace log4Esp
{

class Appender
{

public:
  enum Level
  {
    FATAL = 0,
    ERROR = 1,
    WARNING = 2,
    VERBOSE = 3,
    TRACE = 4
  };

  typedef std::function<void(Print &output, Level level, const char *msg, va_list *args)> FormatterFunction;

  typedef std::function<bool(Level level, const char *msg, va_list *args)> FilterFunction;

  /*
       Return output reference.
       */
  virtual Print &getOutput() = 0;

  /*
       Return associated Formatter.
       */
  Appender::FormatterFunction getFormatter();

  /*
       Set Formatter.
       */
  void setFormatter(FormatterFunction formatterFunction);

  /*
       Return all associated Filter.
       */
  std::vector<Appender::FilterFunction> &getFilter();

  /*
       Add a Filter.
       */
  void addFilter(FilterFunction filterFunction);

  /*
       Set a certain logging Level.
       */
  void setLevel(Level level);

  /*
       Print log entry.
       */
  void print(Level level, const char *msg, va_list *args);

  /*
       Return a default Formatter instance.
       */
  static Appender::FormatterFunction getDefaultFormatter();

  /*
       Output Level.
       */
  static const __FlashStringHelper *toString(Level level, bool shortName = true);

protected:
  /*
       Hook before print log entry is executed.
       */
  virtual void begin(Level level, const char *msg, va_list *args) = 0;

  /*
       Hook after print log entry is executed.
       */
  virtual void end(Level level, const char *msg, va_list *args) = 0;

private:
  FormatterFunction _formatterFunction = NULL;

  std::vector<FilterFunction> _filterFunctions;
};
}

#endif // APPENDER_H
