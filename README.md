# log4Esp - Extendable logging library for ESP8266

[![Build Status](https://travis-ci.org/hunsalz/log4Esp.svg?branch=master)](https://travis-ci.org/hunsalz/log4Esp)
[![Documentation Status](https://readthedocs.org/projects/log4esp/badge/?version=latest)](http://log4esp.readthedocs.io/en/latest/?badge=latest)
[![License](https://img.shields.io/badge/license-MIT%20License-blue.svg)](http://doge.mit-license.org)

 log4Esp is a light-wight logging library for ESP8266. As the name suggest it’s inspired by other [Apache logging services](https://logging.apache.org/).

## Features

* Support of different log levels (FATAL, ERROR, WARNING, VERBOSE, TRACE)
* Support of [printf](http://www.cplusplus.com/reference/cstdio/printf/) standards
* Support of formatted strings in flash memory / [PROGMEM on ESP8266](http://arduino-esp8266.readthedocs.io/en/latest/PROGMEM.html)
* Support of multiple different log destination appenders
* Support of filter options for log events
* Support of adjustable output formats
* Easily extend to your own logging routines

## Quick start

```c++
    Serial.begin(115200);
    while (!Serial && !Serial.available());      
    
    int d = 392;
    uint16_t u = 7235;
    uint16_t o = 10; // 12 octal
    uint16_t x = 15; // f
    uint16_t X = 15; // F
    float f = 392.65;
    float F = 392.65;
    float e = 3.9265e+2;
    float E = 3.9265e+2;
    float g = 392.65;
    float G = 392.65;
    String s = "sample";
    char c = 'a‘;
    
    // use of global LOG instance with default SerialAppender
    LOG.verbose("int = [%d]", d);                           // [V] int = [392]
    LOG.verbose("uint16_t = [%u]", u);                      // [V] uint16_t = [7235]
    LOG.verbose("octal = [%o]", o);                         // [V] octal = [12]
    LOG.verbose("hexadecimal = [%x]", x);                   // [V] hexadecimal = [f]
    LOG.verbose("hexadecimal uppercase = [%X]", X);         // [V] hexadecimal uppercase = [F]
    LOG.verbose("float (f) = [%f]", f);                     // [V] float (f) = [392.649994]
    LOG.verbose("float (F) = [%F]", F);                     // [V] float (F) = [3.92649994F+02]
    LOG.verbose("float (e) = [%e]", e);                     // [V] float (e) = [3.926500e+02]
    LOG.verbose("float (E) = [%E]", E);                     // [V] float (E) = [3.926500E+02]
    LOG.verbose("float (g) = [%g]", g);                     // [V] float (g) = [392.65]
    LOG.verbose("float (G) = [%G]", G);                     // [V] float (G) = [392.65]
    LOG.verbose("String = [%s]", s.c_str());                // [V] String = [sample]
    LOG.verbose("char = [%c]", c);                          // [V] char = [a]
    LOG.verbose(F("PROGMEM"));                              // [V] PROGMEM
    LOG.verbose("%%");                                      // [V] %
    LOG.verbose("%s(%s:%d)", __func__, __FILE__, __LINE__); // [V] foo(..<path>/foo.ino:123)
```

# Samples

- [AdvancedDemo](https://github.com/hunsalz/log4Esp/tree/master/examples/AdvancedDemo) - extends Formatter with Unix timestamp, time date, uptime & free RAM information
- [BasicDemo](https://github.com/hunsalz/log4Esp/tree/master/examples/BasicDemo) - shows the basic usage
- [RollingFileDemo](https://github.com/hunsalz/log4Esp/tree/master/examples/RollingFileDemo) - explains usage of a RollingFileAppender

# Dependencies

This library depends solely on [ESP8266 core for Arduino](https://github.com/esp8266/Arduino.git)

# Contribution

Feel encouraged to give feedback or send pull requests on Github.

# License

log4Esp is open-source software licensed under the [MIT license](http://opensource.org/licenses/MIT). For the full copyright and license information, please see the [LICENSE](LICENSE) file that was distributed with this source code.

# Disclaimer

log4Esp is designed for the ESP8266 device only. Other [MCU](https://en.wikipedia.org/wiki/Microcontroller) like Arduino, etc. are not supported.