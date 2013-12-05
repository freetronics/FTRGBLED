This is an Arduino library for the Freetronics RGBLED module, based on the WS2801 LED controller chip.

http://www.freetronics.com/products/rgb-led-module

![RGBLED Module](http://cdn.shopify.com/s/files/1/0045/8932/products/RGBLED-angle_large.png?v=1321869965)

Supported on Arduino 1.0.5 or newer, or Arduino 1.5.4 or newer.

# Usage

The library ships with 3 examples which you can find under File -> Examples -> FTRGBLED. Adapting an example is the easiest way to get started.

## Include library

At the very top of your sketch, include the library:

    #include <FTRGBLED.h>

## Declare RGBLEDChain

Near the top of the sketch but after the include line, declare a RGBLEDChain like this:

    RGBLEDChain leds(NUM_LEDS, PIN_CKI, PIN_SDI);

NUM_LEDS is the number of LEDs in the chain.

PIN_CKI and PIN_SDI are the pin numbers for the CKI and SDI pins on the module.

## Setup section - call begin

In the setup method, call begin() on the RGBLEDChain like this:

    void setup() {
        leds.begin();
    }

## Set colours

To set individual colours, call setLED():

    leds.setLED(0, LED_YELLOW);

The first parameter is the LED number (starting from zero.)

The second parameter is the LED colour.The library predefines some constants for colours - LED_WHITE, LED_BLACK, LED_RED, LED_GREEN, LED_YELLOW, LED_VIOLET.

You can also specify a colour as { Red, Green, Blue } values. Either like this:

    leds.setLED(0, { 200, 100, 0 });

Or like this:

    const FTLEDColour MY_COLOUR = { 200, 100, 0 };
    leds.setLED(0, MY_COLOUR);

To set all the LEDs to the same colour, use the `setLEDs()` method:

    leds.setLEDs(LED_GREEN);

Calling setLED and setLEDs doesn't change the colours of the LEDs though. To actually change the colours you have to call `update()`:

    leds.update();

This means you can set multiple LEDs to different colours, and then call `update()` once to save time.


# Copyright & License

Copyright (C) 2013 Freetronics Pty Ltd.
Released under the GNU Lesser General Public License V3 as described in the LICENSE file.
