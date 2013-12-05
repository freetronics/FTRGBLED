#include <SPI.h>
#include <FTRGBLED.h>

/* Creates a colour wheel effect by varying the hue of each LED.

   Set NUM_LEDS to the number of LEDs you have connected in a chain.
   The hues for each LED will be distributed evenly around the colour
   wheel.

   You can also set NUM_LEDS to more LEDs than you have (like 10 or 12), even if you don't have that many LEDs, in order
   to see several adjacent hue values on a smaller number of LEDs (the sketch is updating the other non-existent LEDs as well,
   you just can't see them.)
 */
const int NUM_LEDS = 8;

// Pin numbers for the CKI and SDI pin connections
const int PIN_CKI = 2;
const int PIN_SDI = 3;

RGBLEDChain leds(NUM_LEDS, PIN_CKI, PIN_SDI);

// An array to hold the current "angle" on the colour wheel for each LED
float angles[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  leds.begin();
  // Initialise the angles evenly distributed around the colour wheel
  for(int i = 0; i < NUM_LEDS; i++) {
    angles[i] = (i * 2 * PI) / NUM_LEDS;
  }
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
    FTLEDColour colour;
    colour.red = angle_to_channel(angles[i]);
    colour.green = angle_to_channel(angles[i]-2*PI/3);
    colour.blue = angle_to_channel(angles[i]-4*PI/3);
    angles[i] += 0.005;
    if(angles[i] > PI)
       angles[i] -= 2 * PI;
    leds.setLED(i, colour);
  }
  leds.update();
}

// Translate a hue "angle" -120 to 120 degrees (ie -2PI/3 to 2PI/3) to
// an 8-bit R channel value
//
// This is quite slow on a microcontroller, but quick enough for a demo like this!
int angle_to_channel(float a) {
  if(a < -PI)
    a += 2*PI;
  if(a < -2*PI/3  || a > 2*PI/3)
    return 0;
  float f_channel = cos(a*3/4); // remap 120-degree 0-1.0 to 90 ??
  return ceil(f_channel * 255);
}

