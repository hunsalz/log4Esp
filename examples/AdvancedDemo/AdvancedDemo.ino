#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Log4Esp.h>
#include <TimeLib.h>
#include <WiFiUdp.h>

// const char *WIFI_SSID = "xxx"; //  Your WiFi network SSID (name)
// const char *WIFI_PSK = "xxx";  // Your WiFi network PSK (password)

static const char ntpServerName[] = "europe.pool.ntp.org";
const int timeZone = 1; // Central European Time

WiFiUDP Udp;

void setup() {

  // setup Serial output
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  while (!Serial && !Serial.available());
  delay(300);
  Serial.println();

  // setup WiFi
  uint8_t retries = 30;
  uint8_t i = retries;
  bool line_feed = true;
  WiFi.enableSTA(true);
  WiFi.setAutoConnect(true);
  WiFi.persistent(false);
  static WiFiEventHandler CONNECT_HANDLER = WiFi.onStationModeConnected([&](const WiFiEventStationModeConnected &event) {
    if (line_feed) {
      line_feed = false;
      Serial.println();
    }
    LOG.verbose(F("Connected with WiFi station after [%d] attempts"), retries - i);
  });
  static WiFiEventHandler GOT_IP_HANDLER = WiFi.onStationModeGotIP([&](const WiFiEventStationModeGotIP &event) {
    if (line_feed) {
      line_feed = false;
      Serial.println();
    }
    LOG.verbose(F("Received IP [%s] from WiFi station."), event.ip.toString().c_str());
  });
  ESP8266WiFiMulti wifiMulti;
  wifiMulti.addAP(WIFI_SSID, WIFI_PSK);
  LOG.verbose(F("Connecting to WiFi network"));
  while (wifiMulti.run() != WL_CONNECTED && i-- > 0) {
    Serial.print(".");
    delay(300);
  }
  if (line_feed) {
    line_feed = false;
    Serial.println();
  }
  if (retries <= 0) {
    LOG.error(F("Couldn't establish any WiFi connection."));
  }

  // setup UDP
  Udp.begin(8888);
  LOG.verbose(F("Starting UDP with port %d"), Udp.localPort());

  // setup sync provider
  setSyncProvider(getNtpTime);
  setSyncInterval(300);

  // setup a formatter that output current timestamp
  LOG.addFormatterToAll([](Print &output, Appender::Level level, const char *msg, va_list *args) {

    // output log level
    output.print(Appender::toString(level, true));
    output.print(Appender::DEFAULT_SEPARATOR);
    // output UNIX timestamp
    if (timeStatus() != timeNotSet) {
      output.printf("%d", now());
    } else {
      output.printf("%010d", 0);
    }
    output.print(Appender::DEFAULT_SEPARATOR);
    // output date time
    if (timeStatus() != timeNotSet) {
      output.printf("%d-%02d-%02dT%02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());
    } else {
      output.printf("%d-%02d-%02dT%02d:%02d:%02d", 1970, 1, 1, 0, 0, 0);
    }
    output.print(Appender::DEFAULT_SEPARATOR);
    // output uptime of this program in milliseconds
    output.print(millis());
    output.print(Appender::DEFAULT_SEPARATOR);
    // output free heap space
    output.print(ESP.getFreeHeap());
    output.print(Appender::DEFAULT_SEPARATOR);
    // determine buffer length for formatted data
    size_t length = vsnprintf(NULL, 0, msg, *args) + 1;
    char buffer[length];
    // output formatted data
    vsnprintf(buffer, length, msg, *args);
    output.print(buffer);
  });
}

void loop() {

  float value = random(10, 100) / 100.0;
  LOG.verbose(F("Sensor value %.2f"), value);

  delay(2000);
}

const int NTP_PACKET_SIZE = 48;     // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming & outgoing packets

time_t getNtpTime() {
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0); // discard any previously received packets

  // get a random server from the pool
  //WiFi.hostByName(ntpServerName, ntpServerIP);
  ntpServerIP.fromString("212.18.3.19");


  LOG.verbose(F("Request NTP server: %s -> %s"), ntpServerName, ntpServerIP.toString().c_str());

  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {

      LOG.verbose(F("Received NTP response"));

      Udp.read(packetBuffer, NTP_PACKET_SIZE); // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 = (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }

  LOG.error(F("No NTP response received from: %s -> %s"), ntpServerName, ntpServerIP.toString().c_str());

  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[1] = 0;          // Stratum, or type of clock
  packetBuffer[2] = 6;          // Polling Interval
  packetBuffer[3] = 0xEC;       // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); // NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}