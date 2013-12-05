#include <SPI.h>
#include <FTRGBLED.h>

/*
 An updated version of the classic Blink sketch - but in full dazzling colour this time!
 */

// Pins the RGBLED module are connected to
const int PIN_CKI = 2;
const int PIN_SDI = 3;

/* What colour should the LED blink?

   There are some common colours already defined in FTREGLED.h - 
   LED_WHITE, LED_BLACK, LED_RED, LED_GREEN, LED_YELLOW, LED_VIOLET.
  
   Alternatively you can specify colours as individual channel values, taking
   the format { Red, Green, Blue } with range 0-255 - ie LED_RED can also be
   represented as { 255, 0, 0 }
 */
const FTLEDColour BLINK_COLOUR = LED_VIOLET;

RGBLEDChain led(1, PIN_CKI, PIN_SDI);

void setup() {
  led.begin();
}

void loop() {  
  led.setLED(0, BLINK_COLOUR);
  led.update();  
  
  delay(1000);

  led.setLED(0, LED_BLACK);
  led.update();  

  delay(1000);
}


