#include <Logger.h>
#include <RollingFileAppender.h>

#include <FS.h> // https://github.com/esp8266/Arduino/tree/master/cores/esp8266/FS.h

using log4arduino::Logger;
using log4arduino::RollingFileAppender;

const char* FILENAME = "/test-05.log";

void writeLogFile(Logger log) {

  // write the first two verse of a poem from Johann Wolfgang von Goethe to file
  log.verbose("Der Zauberlehrling");
  log.verbose("");
  log.verbose("Hat der alte Hexenmeister");
  log.verbose("Sich doch einmal wegbegeben!");
  log.verbose("Und nun sollen seine Geister");
  log.verbose("Auch nach meinem Willen leben.");
  log.verbose("Seine Wort und Werke");
  log.verbose("Merkt ich und den Brauch,");
  log.verbose("Und mit Geistesstärke");
  log.verbose("Tu ich Wunder auch.");

  log.verbose("Walle! walle");
  log.verbose("Manche Strecke,");
  log.verbose("Daß, zum Zwecke,");
  log.verbose("Wasser fließe");
  log.verbose("Und mit reichem, vollem Schwalle");
  log.verbose("Zu dem Bade sich ergieße.");

  log.verbose("https://de.wikipedia.org/wiki/Der_Zauberlehrling");

  log.verbose("Johann Wolfgang von Goethe");
}

void readLogFile() {

  Serial.printf("\nOutput log file: %s\n\n", FILENAME);

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
  while (!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  SPIFFS.begin(); // don't forget to start SPIFFS first

  Logger log;
  log.getAppender().push_back(new RollingFileAppender(FILENAME, 32, 10, true));

  writeLogFile(log);
  readLogFile();
}

void loop() {
  // time for RTOS functions
  delay(200);
}
