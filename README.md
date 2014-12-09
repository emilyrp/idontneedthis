firewalkerdemo
==============

Dependencies
------------
* [Arduino w/ Flora](https://learn.adafruit.com/getting-started-with-flora/download-software)
* [firewalkerlib](https://github.com/inkwellsiesta/firewalkerlib)
* [Adafruit_NeoPixel library](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library)

To Read Velostat Sensor Values
-----------------------
* Connect one end of [velostat sensor](https://learn.adafruit.com/firewalker-led-sneakers/make-velostat-step-sensors) 
to GND and one to D9/A9.
* Connect Flora board to computer using USB cable.
* In the Arduino IDE, make a new sketch with the following code:
``` c++
#include <Firewalker.h>

#define STEP_PIN  A9

Firewalker firewalker(STEP_PIN);

void setup() {
   // Initialize values
   firewalker.begin();
}

void loop() {
  // Read step value from analog pin
  firewalker.readStepValue();
  
  // Print analog input to serial port
  Serial.println(firewalker.getStepValue());
  
  // Add a short delay
  delay(200);
}
```
* Choose the correct board (Tools->Board->Arduino Flora) and serial port (Tools->Board-><something with usb>),
and run the sketch.
* Open the Serial Monitor (Tools->Serial Monitor) to read values from the velostat sensor. Try pressing/stepping
on the sensor to determine what the "step on threshold" and "step off threshold" values are for you!
