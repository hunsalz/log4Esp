#ifndef APPENDER_H
#define APPENDER_H

#ifdef Arduino_h
// Arduino is not compatible with std::vector
#undef min
#undef max
#endif
#include <vector>
#include <functional>

#include <Arduino.h>

namespace log4Esp {

/**
 * Appenders represent a logging destination.
 */
class Appender {

public:
  static const char DEFAULT_SEPARATOR = '|';

  enum Level { FATAL = 0, ERROR = 1, WARNING = 2, VERBOSE = 3, TRACE = 4 };

  typedef std::function<void(Print &output, Level level, const char *msg, va_list *args)> FormatterFunction;

  typedef std::function<bool(Level level, const char *msg, va_list *args)> FilterFunction;

  /**
   * \return output reference
   */
  virtual Print &getOutput() = 0;

  /**
   * \return associated Formatter
   */
  Appender::FormatterFunction getFormatter();

  /**
   * \param set Formatter
   */
  void setFormatter(FormatterFunction formatterFunction);

  /**
   * \return all associated Filters
   */
  std::vector<Appender::FilterFunction> &getFilter();

  /**
   * \param add a Filter
   */
  void addFilter(FilterFunction filterFunction);

  /**
   * \param set a certain logging Level
   */
  void setLevel(Level level);

  /**
   * Print a log entry.
   * \param level represents logging level of entry
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  void print(Level level, const char *msg, va_list *args);

  /**
   * \return default Formatter instance
   */
  static Appender::FormatterFunction getDefaultFormatter();

  /**
   * \return Level as String representation
   */
  static const __FlashStringHelper *toString(Level level, bool shortName = true);

protected:
  /**
   * A hook before print log entry is executed.
   * \param level represents logging level of entry
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  virtual void begin(Level level, const char *msg, va_list *args) = 0;

  /**
   * A hook after print log entry is executed.
   * \param level represents logging level of entry
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  virtual void end(Level level, const char *msg, va_list *args) = 0;

private:
  FormatterFunction _formatterFunction = NULL;

  std::vector<FilterFunction> _filterFunctions;
};
} // namespace log4Esp

#endif // APPENDER_H
