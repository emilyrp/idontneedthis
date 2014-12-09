#include <Firewalker.h>
#include <Adafruit_NeoPixel.h>

#define N_LEDS    8
#define STEP_PIN  A9
#define LED_PIN   6

#define STEP_ON_TRIGGER  400
#define STEP_OFF_TRIGGER 550

Firewalker firewalker(N_LEDS, STEP_PIN, STEP_OFF_TRIGGER);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


boolean stepping = false;

void setup() {
   firewalker.begin();
   strip.begin();
}


void loop() {
  firewalker.readStepValue();
  
  if (stepping) {
    if (firewalker.getStepValue() > STEP_OFF_TRIGGER) {
      stepping = false;
      for (int i = 0; i < N_LEDS; ++i) {
        strip.setPixelColor(i, BLACK);
      }
    }
  }
  else if (firewalker.getStepValue() < STEP_ON_TRIGGER) {
    stepping = true;
    for (int i = 0; i < N_LEDS; ++i) {
       strip.setPixelColor(i, WHITE);
    }
  } 
  
  // Print analog input to serial port
  Serial.println(firewalker.getStepValue());
  
  strip.show();
  delay(200);
}
