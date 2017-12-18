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
  
  LOG.getAppender().at(0).setFilter([](Appender::Level level, const char* msg, va_list *args) -> bool {
    
    Serial.printf("FILTER CALLED :: Level[%d] == Level[%d]\n", level, Appender::Level::NOTICE);
    if (level == Appender::Level::NOTICE) {
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
  
  LOG.setLevelToAll(Appender::ERROR);
  //LOG.getAppender().at(0).setLevel(Appender::ERROR);
  testPrintf(LOG);
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

  String str = "String";
  char c = 'x';
  float f = 123.123;

  logger.notice("Type String = [%s]", str.c_str());
  logger.notice("Type char = [%c]", c);
  logger.notice("Type float = [%.6g]", f);
  logger.notice("%s(%s:%d)", __func__, __FILE__, __LINE__);
}

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while(!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  //callDefaultLogger();

  //callDefaultLoggerWithFilter();

  callDefaultLoggerWithLevelFilter();

  //callMyLoggerWithoutAppender();

  //callMyLoggerWithAppender();





  // Serial.println("===============================================");
  // Serial.println("==== Default Logger and MyLogger combined =====");
  // Serial.println("===============================================");
  
  // LOG.add(appender);

  // LOG.notice("Type String = [%s]", str.c_str());
  // LOG.notice("Type char = [%c]", c);
  // LOG.notice("Type float = [%.6g]", f);
  // LOG.notice("%s(%s:%d)", __func__, __FILE__, __LINE__); 
}

void loop() {
  // time for RTOS functions
  delay(200);
}
