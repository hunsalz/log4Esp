#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log

#include <Logger.h>

using log4arduino::Logger;
using log4arduino::Appender;

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while(!Serial && !Serial.available()) {}
  delay(300);
  Serial.println();

  float f = 123.123;
  String str = "String";
  char ch = 'x';

  Serial.println("==== CASE 1 =====");
  log4arduino::LOG.notice("String = [%s] Char = [%c] float = [%.6g] - %s(%s:%d)", str.c_str(), ch, f, __func__, __FILE__, __LINE__);

  Serial.println("==== CASE 2 =====");
  Logger logger = Logger("MyLogger");
  logger.notice("String = [%s] Char = [%c] float = [%.6g] - %s(%s:%d)", str.c_str(), ch, f, __func__, __FILE__, __LINE__);

  Serial.println("==== CASE 3 =====");
  logger.notice("String = [%s] Char = [%c] float = [%.6g] - %s(%s:%d)", str.c_str(), ch, f, __func__, __FILE__, __LINE__);

  Appender appender = Appender(&Serial);
  appender.setFormatter([](Print& output, Appender::Level level, const char* msg, va_list *args) {
    
    output.print(F("[TIME]["));
    output.print(Appender::toString(level));
    output.print(F("] "));
    size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
    char buffer[length];
    vsnprintf(buffer, length, msg, *args);
    output.print(buffer);
    output.println();
  });
  log4arduino::LOG.add(appender);
  
  Serial.println("==== CASE 4 =====");
  log4arduino::LOG.notice("String = [%s] Char = [%c] float = [%.6g] - %s(%s:%d)", str.c_str(), ch, f, __func__, __FILE__, __LINE__);
}

void loop() {
  // time for RTOS functions
  delay(200);
}
