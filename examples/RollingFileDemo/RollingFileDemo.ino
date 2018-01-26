#include <Log4Esp.h>

#include <FS.h> // https://github.com/esp8266/Arduino/tree/master/cores/esp8266/FS.h

const char *FILENAME = "/poem.log";
Logger _logger;

void writeLogFile() {
  // write the first two verse of a poem from Johann Wolfgang von Goethe to file
  _logger.verbose("Der Zauberlehrling");
  _logger.verbose("");
  _logger.verbose("Hat der alte Hexenmeister");
  _logger.verbose("Sich doch einmal wegbegeben!");
  _logger.verbose("Und nun sollen seine Geister");
  _logger.verbose("Auch nach meinem Willen leben.");
  _logger.verbose("Seine Wort und Werke");
  _logger.verbose("Merkt ich und den Brauch,");
  _logger.verbose("Und mit Geistesstärke");
  _logger.verbose("Tu ich Wunder auch."); // <-- rollover after this line

  _logger.verbose("Walle! walle");
  _logger.verbose("Manche Strecke,");
  _logger.verbose("Daß, zum Zwecke,");
  _logger.verbose("Wasser fließe");
  _logger.verbose("Und mit reichem, vollem Schwalle");
  _logger.verbose("Zu dem Bade sich ergieße.");

  _logger.verbose("https://de.wikipedia.org/wiki/Der_Zauberlehrling");

  _logger.verbose("Johann Wolfgang von Goethe");
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
  while (!Serial && !Serial.available()) {
  };
  delay(300);
  Serial.println();

  SPIFFS.begin(); // don't forget to start SPIFFS first

  _logger.getAppender().push_back(new RollingFileAppender(FILENAME, 32, 10, true));

  writeLogFile();
  readLogFile();
}

void loop() {
  // time for RTOS functions
  delay(200);
}