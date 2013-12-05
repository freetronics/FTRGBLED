#include <SPI.h>
#include <FTRGBLED.h>

/* This sketch cycles through all of the RGBLEDs showing one with ON_COLOUR and the rest
   with OFF_COLOUR (OFF_COLOUR defaults to black ie LED off.)

   Set NUM_LEDS to the number of LEDs you have connected. When NUM_LEDs is 1, the LED
   will just be solid on (with ON_COLOUR.) For higher numbers you'll get the chaser effect.
 */

const int NUM_LEDS = 2;

// Pins the RGBLED module are connected to
const int PIN_CKI = 2;
const int PIN_SDI = 3;

/* Colours can be specified like this, with individual values
   for each channel as { Red, Green, Blue } with range 0-255.
 */
const FTLEDColour ON_COLOUR = { 100, 40, 0 };

/* Alternatively there are some common colours already defined in FTREGLED.h - 
   LED_WHITE, LED_BLACK, LED_RED, LED_GREEN, LED_YELLOW, LED_VIOLET.
 */
const FTLEDColour OFF_COLOUR = LED_BLACK;

RGBLEDChain leds(NUM_LEDS, PIN_CKI, PIN_SDI);

// Which LED is currently the one that is "on"?
byte on_led = 0;

void setup() {
  Serial.begin(115200);
  leds.begin();
}

void loop() {  
  // Set all LEDs to OFF_COLOUR (doesn't do anything until we call update)
  for(int i = 0; i < NUM_LEDS; i++) {
    leds.setLED(i, OFF_COLOUR);
  }
  // Set the one LED to on_colour
  leds.setLED(on_led, ON_COLOUR);
  
  // Update the LEDs
  leds.update();  
  
  delay(250);
  
  // Increment on_led for the next run of the loop
  on_led++;
  if(on_led == NUM_LEDS)
    on_led = 0;
}

