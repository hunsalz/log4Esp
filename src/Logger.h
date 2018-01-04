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

#include "Appender.h"
#include "SerialAppender.h"

namespace log4Esp {

  class Logger {

    public:

      Logger(const char* name = "default", bool addDefaultSerialAppender = true);

      /*
       Print a log entry in [fatal] mode to all associated Appender.
       */
      template <class T, typename... Args> 
      void fatal(T msg, Args... args) {
        
        print(Appender::FATAL, msg, args...);
      }

      /*
       Print a log entry in [error] mode to all associated Appender.
       */
      template <class T, typename... Args> 
      void error(T msg, Args... args) {
        
        print(Appender::ERROR, msg, args...);
      }

      /*
       Print a log entry in [warning] mode to all associated Appender.
       */
      template <class T, typename... Args> 
      void warning(T msg, Args... args) {
        
        print(Appender::WARNING, msg, args...);
      }

      /*
       Print a log entry in [verbose] mode to all associated Appender.
       */
      template <class T, typename... Args> 
      void verbose(T msg, Args... args) {
        
        print(Appender::VERBOSE, msg, args...);
      }

      /*
       Print a log entry in [trace] mode to all associated Appender.
       */
      template <class T, typename... Args> 
      void trace(T msg, Args... args) {
        
        print(Appender::TRACE, msg, args...);
      }

      /*
       Return internal logger name.
       */
      const char* getName();

      /*
       Return list of Appender.
       */
      std::vector<Appender*>& getAppender();

      /*
       Add same Formatter to all associated Appender.
       */
      void addFormatterToAll(Appender::FormatterFunction formatterFunction);

      /*
       Add same Filter to all associated Appender.
       */
      void addFilterToAll(Appender::FilterFunction filterFunction);

      /*
       Add same logging Level to all associated Appender.
       */
      void addLevelToAll(Appender::Level level);

      /*
       Print log entry to all associated Appender.
       */
      template <class T>
      void print(Appender::Level level, T msg, ...) {
        
        va_list args;
        va_start(args, msg);
        String str = String(msg); // use String constructor to handle PROGMEN and other character representations
        for (auto && fn : _appender) {
          fn->print(level, str.c_str(), &args);
        }
        va_end(args);
      }

    private:

      const char* _name;

      std::vector<Appender*> _appender;
  };

  extern Logger LOG;
}

#endif // LOGGER_H
