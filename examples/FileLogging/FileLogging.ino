#include <Logger.h>
#include <RollingFileAppender.h>

#include <FS.h> // https://github.com/esp8266/Arduino/tree/master/cores/esp8266/FS.h

using log4arduino::Logger;
using log4arduino::LOG;
using log4arduino::Appender;
using log4arduino::RollingFileAppender;

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while(!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  SPIFFS.begin();

  Logger logger = Logger("MyLogger");

  RollingFileAppender appender = RollingFileAppender("/test.log");
  logger.getAppender().push_back(appender);

  logger.verbose("TEST RollingFileAppender");
}

void loop() {
  // time for RTOS functions
  delay(200);
}