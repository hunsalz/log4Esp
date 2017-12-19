#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log

#include <Logger.h>

using log4arduino::Logger;
using log4arduino::LOG;
using log4arduino::Appender;

void callDefaultLogger() {
  
  Serial.println("=========================");
  Serial.println("==== Default Logger =====");
  Serial.println("=========================");
  testPrintf(LOG);
}

void callDefaultLoggerWithFilter() {
  
  Serial.println("=====================================");
  Serial.println("==== Default Logger with Filter =====");
  Serial.println("=====================================");
  
  //LOG.addFilterToAll(...);
  LOG.getAppender().at(0).addFilter([](Appender::Level level, const char* msg, va_list *args) -> bool {
    
    Serial.printf("FILTER CALLED :: Level[%d] == Level[%d]\n", level, Appender::Level::VERBOSE);
    if (level == Appender::Level::VERBOSE) {
      return true;
    } else {
      return false;
    }
  });
  testPrintf(LOG);
}

void callDefaultLoggerWithLevelFilter() {
  
  Serial.println("===========================================");
  Serial.println("==== Default Logger with Level filter =====");
  Serial.println("===========================================");
  
  LOG.addLevelToAll(Appender::ERROR);
  //LOG.getAppender().at(0).setLevel(Appender::ERROR);
  LOG.fatal("A fatal message");
  LOG.error("An error message");
  LOG.warning("A warning message"); // won't be displayed with level definition ERROR
  LOG.verbose("A notice message"); // won't be displayed with level definition ERROR
  LOG.verbose("A verbose message"); // won't be displayed with level definition ERROR
}

void callMyLoggerWithoutAppender() {
  
  Serial.println("========================================");
  Serial.println("==== MyLogger without any Appender =====");
  Serial.println("========================================");
  testPrintf(Logger("MyLogger"));
}

void callMyLoggerWithAppender() {
  
  Serial.println("=================================");
  Serial.println("==== MyLogger with Appender =====");
  Serial.println("=================================");

  // Logger logger = Logger("MyLogger");
  // Appender appender = Appender(&Serial);
  // appender.setFormatter([](Print& output, Appender::Level level, const char* msg, va_list *args) {
    
  //   output.print(F("[TIME]["));
  //   output.print(Appender::toString(level));
  //   output.print(F("] "));
  //   size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
  //   char buffer[length];
  //   vsnprintf(buffer, length, msg, *args);
  //   output.print(buffer);
  //   output.println();
  // });
  // logger.add(appender);

  // testPrintf(logger);
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
  logger.verbose("%%");
  logger.verbose("%s(%s:%d)", __func__, __FILE__, __LINE__);
}

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while(!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  callDefaultLogger();

  //callDefaultLoggerWithFilter();

  callDefaultLoggerWithLevelFilter();

  //callMyLoggerWithoutAppender();

  //callMyLoggerWithAppender();





  // Serial.println("===============================================");
  // Serial.println("==== Default Logger and MyLogger combined =====");
  // Serial.println("===============================================");
  
  // LOG.add(appender);

  // LOG.verbose("Type String = [%s]", str.c_str());
  // LOG.verbose("Type char = [%c]", c);
  // LOG.verbose("Type float = [%.6g]", f);
  // LOG.verbose("%s(%s:%d)", __func__, __FILE__, __LINE__); 
}

void loop() {
  // time for RTOS functions
  delay(200);
}
