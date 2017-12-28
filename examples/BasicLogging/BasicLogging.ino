#include <Logger.h>
#include <SerialAppender.h>

using log4arduino::Logger;
using log4arduino::LOG;
using log4arduino::Appender;
using log4arduino::SerialAppender;

void callDefaultLogger() {
  
  Serial.println("+----------------+");
  Serial.println("| Default Logger |");
  Serial.println("+----------------+");
  
  testPrintf(LOG);
}

void callMyLoggerWithAppender() {
  
  Serial.println("+------------------------+");
  Serial.println("| MyLogger with Appender |");
  Serial.println("+------------------------+");

  testPrintf(Logger("MyLogger"));
}

void callMyLoggerWithoutAppender() {
  
  Serial.println("+-------------------------------+");
  Serial.println("| MyLogger without any Appender |");
  Serial.println("+-------------------------------+");
  
  testPrintf(Logger("MyLogger", false)); // won't display anything without any Appender
}

void callMyLoggerWithFilter() {
  
  Serial.println("+----------------------------+");
  Serial.println("| Default Logger with Filter |");
  Serial.println("+----------------------------+");
  
  Logger logger = Logger("MyLogger");
  // use one of two possible methods to add an Filter
  // logger.addFilterToAll(...); // adding Filter to all Appenders
  logger.getAppender().at(0)->addFilter([](Appender::Level level, const char* msg, va_list *args) -> bool { // adding filter to only one specific appender
    
    if (strstr(msg, "float")) {
      Serial.printf("Suppress messages containing 'float'");
      return true;
    } else {
      return false;
    }
  });
  
  testPrintf(logger);
}

void callMyLoggerWithLevelFilter() {
  
  Serial.println("+----------------------------------+");
  Serial.println("| Default Logger with Level filter |");
  Serial.println("+----------------------------------+");
  
  Logger logger = Logger("MyLogger");
  // use one of two possible methods to add an Level filter
  logger.addLevelToAll(Appender::ERROR); // adding Level filter to all Appenders
  // logger.getAppender().at(0).setLevel(Appender::ERROR); // adding Level filter to only one specific Appender
  logger.fatal("A fatal message");
  logger.error("An error message");
  logger.warning("A warning message"); // won't be displayed with level definition ERROR (see above)
  logger.verbose("A notice message"); // won't be displayed with level definition ERROR (see above)
  logger.verbose("A verbose message"); // won't be displayed with level definition ERROR (see above)
}

void callAppenderWithMyFormatter() {
   
  Serial.println("+-----------------------------+");
  Serial.println("| Appender with own Formatter |");
  Serial.println("+-----------------------------+");

  Logger logger = Logger("MyLogger");
  // use one of two possible methods to add an Level filter
  // logger.getAppender().at(0).setFomatter(...); // adding Formatter to only one specific Appender
  logger.addFormatterToAll([](Print& output, Appender::Level level, const char* msg, va_list *args) { // adding formatter to all Appenders

    output.print(F("[MyLogger]["));
    output.print(F("["));
    output.print(Appender::toString(level, true));
    output.print(F("] "));
    size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
    char buffer[length];
    vsnprintf(buffer, length, msg, *args);
    output.print(buffer);
  });

  testPrintf(logger);
}

void callMultipleAppender() {
  
  Serial.println("+--------------------+");
  Serial.println("| Multiple Appenders |");
  Serial.println("+--------------------+");

  Logger logger = Logger("MyLogger");
  logger.getAppender().push_back(new SerialAppender());

  testPrintf(logger);
}

void testPrintf(Logger logger) {

  // http://www.cplusplus.com/reference/cstdio/printf/

  int d = 392;
  uint16_t u = 7235;
  uint16_t o = 10; // 12 octal
  uint16_t x = 15; // f
  uint16_t X = 15; // F
  float f = 392.65;
  float F = 392.65;
  float e = 3.9265e+2;
  float E = 3.9265e+2;
  float g = 392.65;
  float G = 392.65;
  String s = "sample";
  char c = 'a';
  
  logger.verbose("int = [%d]", d);
  logger.verbose("uint16_t = [%u]", u);
  logger.verbose("octal = [%o]", o);
  logger.verbose("hexadecimal = [%x]", x);
  logger.verbose("hexadecimal uppercase = [%X]", X);
  logger.verbose("float (f) = [%f]", f);
  logger.verbose("float (F) = [%F]", F);
  logger.verbose("float (e) = [%e]", e);
  logger.verbose("float (E) = [%E]", E);
  logger.verbose("float (g) = [%g]", g);
  logger.verbose("float (G) = [%G]", G);
  logger.verbose("String = [%s]", s.c_str());
  logger.verbose("char = [%c]", c);
  logger.verbose(F("PROGMEM"));
  logger.verbose("%%");
  logger.verbose("%s(%s:%d)", __func__, __FILE__, __LINE__);
  // logger.verbose("NULL = %s", NULL); // TODO / IDEA: make Logger null pointer safe via argument list check
}

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while (!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  callDefaultLogger();

  callMyLoggerWithAppender();

  callMyLoggerWithoutAppender();

  callMyLoggerWithFilter();

  callMyLoggerWithLevelFilter();

  callAppenderWithMyFormatter();

  callMultipleAppender();
}

void loop() {
  // time for RTOS functions
  delay(200);
}