#ifndef LOGGER_H
#define LOGGER_H

#ifdef Arduino_h
// Arduino is not compatible with std::vector
#undef min
#undef max
#endif
#include <vector>

#include <inttypes.h>
#include <stdarg.h>

#include "appender/Appender.h"
#include "appender/SerialAppender.h"

namespace log4Esp {

class Logger {

  /**
   * Logger represents the central interface to all log operations.
   */
public:
  /**
   * \param name labels internal Logger name
   * \param addDefaultSerialAppender adds a SerialAppender optional
   */
  Logger(const char *name = "default", bool addDefaultSerialAppender = true);

  /**
   * Print a log entry in [fatal] mode to all associated Appenders.
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  template <class T, typename... Args> void fatal(T msg, Args... args) { print(Appender::FATAL, msg, args...); }

  /**
   * Print a log entry in [error] mode to all associated Appenders.
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  template <class T, typename... Args> void error(T msg, Args... args) { print(Appender::ERROR, msg, args...); }

  /**
   * Print a log entry in [warning] mode to all associated Appenders.
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  template <class T, typename... Args> void warning(T msg, Args... args) { print(Appender::WARNING, msg, args...); }

  /**
   * Print a log entry in [verbose] mode to all associated Appenders.
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  template <class T, typename... Args> void verbose(T msg, Args... args) { print(Appender::VERBOSE, msg, args...); }

  /**
   * Print a log entry in [trace] mode to all associated Appenders.
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  template <class T, typename... Args> void trace(T msg, Args... args) { print(Appender::TRACE, msg, args...); }

  /**
   * \return internal Logger name
   */
  const char *getName();

  /**
   * \return list of associated Appenders
   */
  std::vector<Appender *> &getAppender();

  /**
   * \param add same FormatterFunction to all associated Appenders
   */
  void addFormatterToAll(Appender::FormatterFunction formatterFunction);

  /**
   * \param add same Filter to all associated Appenders
   */
  void addFilterToAll(Appender::FilterFunction filterFunction);

  /**
   * \param add same Level to all associated Appenders
   */
  void addLevelToAll(Appender::Level level);

  /**
   * Print a log entry to all associated Appenders.
   * \param level represents logging level of entry
   * \param msg log entry with optional format instructions and placeholders
   * \param args arguments replacing placeholders
   */
  template <class T> void print(Appender::Level level, T msg, ...) {

    va_list args;
    va_start(args, msg);
    String str = String(msg); // use String constructor to handle PROGMEN and other character representations
    for (auto &&fn : _appender) {
      fn->print(level, str.c_str(), &args);
    }
    va_end(args);
  }

private:
  const char *_name;

  std::vector<Appender *> _appender;
};
} // namespace log4Esp

#if !defined(NO_GLOBAL_INSTANCES)
extern log4Esp::Logger LOG;
#endif // NO_GLOBAL_INSTANCES

#endif // LOGGER_H
