# log4Esp [![Build Status](https://travis-ci.org/hunsalz/log4Esp.svg?branch=master)](https://travis-ci.org/hunsalz/log4Esp)

 log4Esp is a light-wight logging library for ESP8266. As the name suggest it’s inspired by other [Apache logging services](https://logging.apache.org/) 

## Features

* Support of different log levels (FATAL, ERROR, WARNING, VERBOSE, TRACE)
* Support of [printf](http://www.cplusplus.com/reference/cstdio/printf/) standards
* Support of formatted strings in flash memory / [PROGMEM on ESP8266](http://arduino-esp8266.readthedocs.io/en/latest/PROGMEM.html)
* Support of multiple different log destination appenders
* Easily to extend with your own logging routines

## Quick start

```c++
    Serial.begin(115200);
    while (!Serial && !Serial.available());    
    // use of global LOG instance with default SerialAppender
    LOG.verbose("int = [%d]", d);
    LOG.verbose("uint16_t = [%u]", u);
    LOG.verbose("octal = [%o]", o);
    LOG.verbose("hexadecimal = [%x]", x);
    LOG.verbose("hexadecimal uppercase = [%X]", X);
    LOG.verbose("float (f) = [%f]", f);
    LOG.verbose("float (F) = [%F]", F);
    LOG.verbose("float (e) = [%e]", e);
    LOG.verbose("float (E) = [%E]", E);
    LOG.verbose("float (g) = [%g]", g);
    LOG.verbose("float (G) = [%G]", G);
    LOG.verbose("String = [%s]", s.c_str());
    LOG.verbose("char = [%c]", c);
    LOG.verbose(F("PROGMEM"));
    LOG.verbose("%%");
    LOG.verbose("%s(%s:%d)", __func__, __FILE__, __LINE__);
```
# Disclaimer

log4Esp is designed for the ESP8266 device only. Other [MCU](https://en.wikipedia.org/wiki/Microcontroller) like Arduino, etc. are not supported.

# Dependencies

This library depends solely on [ESP8266 core for Arduino](https://github.com/esp8266/Arduino.git)

# Contribution

Feel encouraged to give feedback or send pull requests on Github.

# License

log4Esp is open-sourced software licensed under the [MIT license](http://opensource.org/licenses/MIT). For the full copyright and license information, please see the [LICENSE](LICENSE) file that was distributed with this source code.