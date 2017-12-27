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

  SPIFFS.begin(); // don't forget to start SPIFFS first

  LOG.getAppender().push_back(new RollingFileAppender(FILENAME));

  LOG.verbose("Write this text to [%s]", FILENAME); // now, this message is logged to serial and to file

  outputLogFile();
}

void loop() {
  // time for RTOS functions
  delay(200);
}