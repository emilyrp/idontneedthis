#include <Firewalker.h>
#include <Adafruit_NeoPixel.h>

#define N_LEDS    8   // Number of LEDs in the strip
#define STEP_PIN  A9  // The pin that the sensor is connected to
#define LED_PIN   6   // The pin that the LED strip is connected to

#define STEP_DOWN_THRESHOLD  400 // The highest value of the sensor when you're
                                 // definitely stepping down on it
#define STEP_UP_THRESHOLD    550   // The lowest value of the sensor when you're
                                   // definitely not stepping down on it


Firewalker firewalker(STEP_PIN, N_LEDS, STEP_UP_THRESHOLD);
// This variable keeps track of the LED strip
Adafruit_NeoPixel strip =
  Adafruit_NeoPixel(N_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

boolean stepping = false; // This variable keeps track of whether or not
                          // you're stepping down on the sensor

void setup() {
   // Get everything set up
   firewalker.begin();
   strip.begin();
}


void loop() {
  // Read the sensor value from the analog pin
  firewalker.updateSensorValue();
  
  // If the sensor value is higher than the step up threshold
  // we are not stepping on it
  if (firewalker.getSensorValue() > STEP_UP_THRESHOLD) {
    stepping = false;
  }
  
  // If the sensor value is lower than the step down threshold
  // we are stepping on it
  if (firewalker.getSensorValue() < STEP_DOWN_THRESHOLD) {
    stepping = true;
  }
  
  // Update the status of the LED colors
  firewalker.updateStep(stepping);
  
  
  // Set each LED in the strip to the correct color
  for (int i = 0; i < N_LEDS; ++i) {
    strip.setPixelColor(i, firewalker.getLEDColor(i));
  }
  
  // Show the colors on the LED strip
  strip.show();
  
  // Slow down the microcontroller a little so you can
  // see the color pattern!
  delayMicroseconds(1500);
}
