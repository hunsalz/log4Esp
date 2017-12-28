#include <Logger.h>
#include <RollingFileAppender.h>

#include <FS.h> // https://github.com/esp8266/Arduino/tree/master/cores/esp8266/FS.h

using log4arduino::LOG;
using log4arduino::RollingFileAppender;

const char* FILENAME = "/test3.log";

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
  while (!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  SPIFFS.begin(); // don't forget to start SPIFFS first

  LOG.getAppender().push_back(new RollingFileAppender(FILENAME, 32, 10, true));

  // write the first two verse of a poem from Johann Wolfgang von Goethe to file
  LOG.verbose("Der Zauberlehrling");
  LOG.verbose("");
  LOG.verbose("Hat der alte Hexenmeister");
  LOG.verbose("Sich doch einmal wegbegeben!");
  LOG.verbose("Und nun sollen seine Geister");
  LOG.verbose("Auch nach meinem Willen leben.");
  LOG.verbose("Seine Wort und Werke");
  LOG.verbose("Merkt ich und den Brauch,");
  LOG.verbose("Und mit Geistesstärke");
  LOG.verbose("Tu ich Wunder auch.");

  LOG.verbose("Walle! walle");
  LOG.verbose("Manche Strecke,");
  LOG.verbose("Daß, zum Zwecke,");
  LOG.verbose("Wasser fließe");
  LOG.verbose("Und mit reichem, vollem Schwalle");
  LOG.verbose("Zu dem Bade sich ergieße.");

  LOG.verbose("https://de.wikipedia.org/wiki/Der_Zauberlehrling");

  LOG.verbose("Johann Wolfgang von Goethe");

  outputLogFile();
}

void loop() {
  // time for RTOS functions
  delay(200);
}