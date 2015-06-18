#include <FTRGBLED.h>
/* 
  This sketch cycles through all the colors of the rainbow with a 
  generic function. This is an adaptation of a tutorial by jim bumgardner (@jbum on twitter)
  and was written for use on a Arduino Trinket (8Mhz) 
 */
const int PIN_CKI = 2;
const int PIN_SDI = 0;

RGBLEDChain led(1, PIN_CKI, PIN_SDI);

void setup() {
  // put your setup code here, to run once:
  led.begin();
}

void makeColor(float freq1, 
                float freq2, 
                float freq3, 
                float ph1, 
                float ph2, 
                float ph3, 
                int center, 
                int width, 
                int len) {
  double red = 0;
  double blue = 0;
  double green = 0;
  
  for (int i = 0; i < len; i++) {
    red = sin(freq1 * i + ph1) * width + center;
    green = sin(freq2 * i + ph2) * width + center;
    blue = sin(freq3 * i + ph3) * width + center;
    led.setLED(0, {red, green, blue});
    led.update();
    delay(50);
  }
}

void loop() {
  // display rainbow colors
  makeColor(0.3, 0.3, 0.3, 0, 2, 4, 128, 127, 128);
  // display pastels
  makeColor(0.3, 0.3, 0.3, 0, 2, 4, 230, 25, 128);
  
  // for other ideas, reference this: 
  // http://krazydad.com/tutorials/makecolors.php
 
}
