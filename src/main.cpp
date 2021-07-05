#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}


#define NUMPIXELS 64
#define BRIGHTNESS 30
#define Pin 8

int inPin = 2;
int LED_Pin = 8;
int LEDstate = HIGH;
int sensorValue;
int reading; 
int LEDlow = LOW; 
int lastTiltState = HIGH;
long lastDebounceTime = 0; 
long debounceDelay = 50;

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixel.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

Adafruit_NeoPixel pixels(NUMPIXELS, LED_Pin, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // now how to make them fade on a cycle like the rainbow did.
 sensorValue = digitalRead(inPin);
// If the switch changed, due to noise or pressing:
if (sensorValue == lastTiltState) {
// reset the debouncing timer
lastDebounceTime = millis();
}
if ((millis() - lastDebounceTime) > debounceDelay) {
// whatever the reading is at, it's been there for longer
// than the debounce delay, so take it as the actual current state:
lastTiltState = sensorValue;
}
digitalWrite(LED_Pin, lastTiltState);

Serial.println(sensorValue);
delay(500);

if(reading == 1){ 
  digitalWrite(LED_Pin, HIGH); 
  colorWipe(pixels.Color(200,50,20), 50); //PinkDeep 
colorWipe(pixels.Color(255,10,20), 50);
colorWipe(pixels.Color(200,150,20), 50);
colorWipe(pixels.Color(100,150,20), 50);
 } else {
  digitalWrite(LED_Pin, LOW);
  theaterChase(pixels.Color(127, 127, 127), 50); // White
  theaterChase(pixels.Color(127, 0, 0), 50); // Red
  theaterChase(pixels.Color(0, 0, 127), 50); // Blue
} 
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
}
