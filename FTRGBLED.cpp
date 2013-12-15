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

static inline void delay20ns() __attribute__((always_inline));

// If anyone knows of a compiler builtin that will evaluate
// to reg_t already from gcc, please let me know!
#ifdef __AVR__
#define reg_t uint8_t
static inline void delay20ns() { 
  // Not necessary on AVR, max bit-banging rate is a lot less than 25MHz
}
#else
#define reg_t uint32_t

// Delay ~20ns to keep clock to 25Mhz on ARM
// derived from the delayMicroseconds implementation in the Due core
//
// Note: in reality it looks like RGBLED usually requires a somewhat
// slower clock than 25MHz, the high edge this code yields is 100ns+
// wide, needed for everything to work using plain breadboard wires
// (probably capacitance in the wires & breadboard?) With plain port
// writes on Due the high edge is ~60ns wide and this is not wide
// enough for reliable data transmission. Low edge is always wider due
// to loop processing.
static inline void delay20ns(){
  /* 3 cycles per loop, 150MHz would be 20ns per loop */
  uint32_t n = (VARIANT_MCK / 150000000) + 1;
  asm volatile(
               "L_%=_delay20ns:"       "\n\t"
               "subs   %0, #1"                 "\n\t"
               "bge    L_%=_delay20ns" "\n"
               : "+r" (n) :
               );
}

#endif

void RGBLEDChain::update()
{
  if(!data)
    return;
  uint8_t *data_raw = (uint8_t *)data;

  volatile reg_t *port_sdi = portOutputRegister(digitalPinToPort(pin_sdi));
  reg_t mask_sdi = digitalPinToBitMask(pin_sdi);

  volatile reg_t *port_cki = portOutputRegister(digitalPinToPort(pin_cki));
  reg_t mask_cki = digitalPinToBitMask(pin_cki);

  for(int led = 0; led < num_leds*3; led++) {
    uint8_t byte_raw = data_raw[led];
    for(uint8_t bit = 1<<7; bit > 0; bit>>=1) {
      if(byte_raw & bit) {
        *port_sdi |= mask_sdi;
      } else {
        *port_sdi &= ~mask_sdi;
      }
      *port_cki |= mask_cki;
      delay20ns();
      *port_cki &= ~mask_cki;
      // 20ns delay on low edge seems unnecessary at least on Due, loop calculations take at least that long
    }
  }
  delay(1);
}
