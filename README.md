firewalkerdemo
==============

Dependencies
------------
* [Arduino w/ Flora](https://learn.adafruit.com/getting-started-with-flora/download-software)
* [firewalkerlib](https://github.com/inkwellsiesta/firewalkerlib)
* [Adafruit_NeoPixel library](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library)


The Final Code
--------------
without comments:
``` c++
#include <Firewalker.h>
#include <Adafruit_NeoPixel.h>

#define N_LEDS      8
#define SENSOR_PIN  A9
#define LED_PIN     6

#define STEP_DOWN_THRESHOLD  400 
#define STEP_UP_THRESHOLD    550 

boolean stepping = false; 

Firewalker firewalker(SENSOR_PIN, N_LEDS, STEP_UP_THRESHOLD);
Adafruit_NeoPixel strip =                                    
  Adafruit_NeoPixel(N_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
   firewalker.begin();
   strip.begin();
}

void loop() {
  firewalker.updateSensorValue();
  
  if (firewalker.getSensorValue() > STEP_UP_THRESHOLD)
    stepping = false;
  
  if (firewalker.getSensorValue() < STEP_DOWN_THRESHOLD)
    stepping = true;
  
  firewalker.updateStep(stepping);
  
  for (int i = 0; i < N_LEDS; ++i)
    strip.setPixelColor(i, firewalker.getLEDColor(i));
  
  strip.show();
  
  delayMicroseconds(1500);
}
```

To Read Velostat Sensor Values
-----------------------
* Connect one end of [velostat sensor](https://learn.adafruit.com/firewalker-led-sneakers/make-velostat-step-sensors) 
to GND and one to D9/A9.
* Connect Flora board to computer using USB cable.
* In the Arduino IDE, make a new sketch with the following code:
``` c++
#include <Firewalker.h>

#define SENSOR_PIN  A9

Firewalker firewalker(SENSOR_PIN);

void setup() {
   // Initialize values
   firewalker.begin();
}

void loop() {
  // Read step value from analog pin
  firewalker.updateSensorValue();
  
  // Print analog input to serial port
  Serial.println(firewalker.getSensorValue());
  
  // Add a short delay
  delay(200);
}
```
* Choose the correct board (Tools->Board->Arduino Flora) and serial port (Tools->Port->something with USB),
and run the sketch.
* Open the Serial Monitor (Tools->Serial Monitor) to read values from the velostat sensor. Try pressing/stepping
on the sensor to determine what the "step on threshold" and "step off threshold" values are for you!
