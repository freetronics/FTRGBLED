#ifndef _FTRGBLED_H
#define _FTRGBLED_H

#include "Arduino.h"

struct FTLEDColour {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} __attribute__((packed));

class RGBLEDChain
{
public:
  RGBLEDChain(int length, byte pin_cki, byte pin_sdi) :
    length(length),
    pin_cki(pin_cki),
    pin_sdi(pin_sdi),
    data(0)
  {
  }

  void begin();
  void setLED(int index, const FTLEDColour &colour);
  void setLED(int index, byte red, byte green, byte blue);
  void update();

  inline FTLEDColour getLED(int index) { return data[index]; }
  byte getRed(int index) { return data[index].red; }
  byte getGreen(int index) { return data[index].green; }
  byte getBlue(int index) { return data[index].blue; }

private:
  int length;
  byte pin_cki;
  byte pin_sdi;
  FTLEDColour *data;
};

#endif
