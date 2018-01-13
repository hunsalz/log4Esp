#include <Log4Esp.h>

using log4Esp::LOG;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while (!Serial && !Serial.available()) {
  };
  delay(300);
  Serial.println();
}

void loop() {
  // TODO

  delay(2000);
}