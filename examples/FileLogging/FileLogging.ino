#include <Logger.h>
#include <RollingFileAppender.h>

#include <FS.h> // https://github.com/esp8266/Arduino/tree/master/cores/esp8266/FS.h

using log4arduino::Logger;
using log4arduino::LOG;
using log4arduino::Appender;
using log4arduino::RollingFileAppender;

const char* FILENAME = "/test.log";

void outputLogFile() {

  Serial.println("+----------------+");
  Serial.println("| Output LogFile |");
  Serial.println("+----------------+");

  if (SPIFFS.exists(FILENAME)) {
    File file = SPIFFS.open(FILENAME, "r");
    String line;
    while (file.available()) {
      line = file.readStringUntil('\n');
      Serial.println(line);
    }
    file.close();
  }
}

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while(!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  SPIFFS.begin();

  // File file = SPIFFS.open(FILENAME, "w+");
  // file.println("SPIFFS TEST 1");
  // file.println("SPIFFS TEST 2");
  // file.println("SPIFFS TEST 3");
  // file.flush();
  // file.close();

  Logger logger = Logger("MyLogger");

  //File file = getFile();
  //file.println("TEST OPEN FILE with getFile()");

  RollingFileAppender* appender = new RollingFileAppender(FILENAME, false);
  appender->setFormatter([&](Print& output, Appender::Level level, const char* msg, va_list *args) { // adding formatter to all Appenders

    // File file = SPIFFS.open(FILENAME, "a+");
    // file.print(F("[FILE]["));
    // file.print(Appender::toString(level, false));
    // file.print(F("] "));
    // size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
    // char buffer[length];
    // vsnprintf(buffer, length, msg, *args);
    // file.print(buffer);
    // file.println();
    // file.flush();
    // file.close();

    Serial.println("Saving output to file");

    output.print(F("[FILE]["));
    output.print(Appender::toString(level, false));
    output.print(F("] "));
    size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
    char buffer[length];
    vsnprintf(buffer, length, msg, *args);
    output.print(buffer);
    output.println();

  });
  logger.getAppender().push_back(appender);

  logger.verbose(">>>>>>>>>>>>>>>>>Write this text to [%s]", FILENAME);

  outputLogFile();
}

void loop() {
  // time for RTOS functions
  delay(200);
}