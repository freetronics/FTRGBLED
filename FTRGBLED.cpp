/* FTRGBLED Library

   See https://github.com/freetronics/FTRGBLED

   Copyright (C) 2013 Freetronics Pty Ltd.
   Licensed under GNU Lesser General Public License V3, as described in the file LICENSE.
*/
#include "FTRGBLED.h"
#include <stdint.h>

void RGBLEDChain::begin()
{
  data = (FTLEDColour *)malloc(num_leds*sizeof(FTLEDColour));
  memset(data, 0, num_leds*sizeof(FTLEDColour));
  pinMode(pin_cki, OUTPUT);
  digitalWrite(pin_cki, LOW);
  pinMode(pin_sdi, OUTPUT);
  update(); // start with everything off
}

void RGBLEDChain::setLED(int index, byte red, byte green, byte blue)
{
  if(!data)
    return;
  data[index].red = red;
  data[index].green = green;
  data[index].blue = blue;
}

void RGBLEDChain::setLED(int index, const FTLEDColour &colour)
{
  setLED(index, colour.red, colour.green, colour.blue);
}

void RGBLEDChain::setLEDs(const FTLEDColour &colour)
{
  for(int i = 0; i < num_leds; i++) {
    setLED(i, colour);
  }
}

void RGBLEDChain::update()
{
  if(!data)
    return;
  uint8_t *data_raw = (uint8_t *)data;

  volatile uint8_t *port_sdi = portOutputRegister(digitalPinToPort(pin_sdi));
  uint8_t mask_sdi = digitalPinToBitMask(pin_sdi);

  volatile uint8_t *port_cki = portOutputRegister(digitalPinToPort(pin_cki));
  uint8_t mask_cki = digitalPinToBitMask(pin_cki);

  for(int led = 0; led < num_leds*3; led++) {
    uint8_t byte_raw = data_raw[led];
    for(uint8_t bit = 1<<7; bit > 0; bit>>=1) {
      if(byte_raw & bit) {
        *port_sdi |= mask_sdi;
      } else {
        *port_sdi &= ~mask_sdi;
      }
      *port_cki |= mask_cki;
      *port_cki &= ~mask_cki;
    }
  }
  delay(1);
}
