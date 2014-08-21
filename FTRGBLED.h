/* FTRGBLED Library

   See https://github.com/freetronics/FTRGBLED

   Copyright (C) 2013 Freetronics Pty Ltd.
   Licensed under GNU Lesser General Public License V3, as described in the file LICENSE.
*/
#ifndef _FTRGBLED_H
#define _FTRGBLED_H

#include "Arduino.h"

struct FTLEDColour {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} __attribute__((packed));

/* Allow American English spelling instead of British English */
#define FTLEDColor FTLEDColour

/* some predefined common colours */
const FTLEDColour LED_BLACK = { 0, 0, 0 };
const FTLEDColour LED_RED = { 255, 0, 0 };
const FTLEDColour LED_GREEN = { 0, 255, 0 };
const FTLEDColour LED_BLUE = { 0, 0, 255 };
const FTLEDColour LED_YELLOW = { 255, 200, 0 };
const FTLEDColour LED_VIOLET = { 255, 0, 200 };
const FTLEDColour LED_WHITE = { 255, 200, 200 };

class RGBLEDChain
{
public:
  RGBLEDChain(int num_leds, byte pin_cki, byte pin_sdi) :
    num_leds(num_leds),
    pin_cki(pin_cki),
    pin_sdi(pin_sdi),
    data(0)
  {
  }

  void begin();
  void setLED(int index, const FTLEDColour &colour);
  void setLED(int index, byte red, byte green, byte blue);
  void setLEDs(const FTLEDColour &colour);
  void update();

  inline FTLEDColour getLED(int index) { return data[index]; }
  byte getRed(int index) { return data[index].red; }
  byte getGreen(int index) { return data[index].green; }
  byte getBlue(int index) { return data[index].blue; }

private:
  int num_leds;
  byte pin_cki;
  byte pin_sdi;
  FTLEDColour *data;
};

#endif
