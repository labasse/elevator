/*!
 * @file Adafruit_NeoPixel.h
 *
 * This is part of Adafruit's NeoPixel library for the Arduino platform,
 * allowing a broad range of microcontroller boards (most AVR boards,
 * many ARM devices, ESP8266 and ESP32, among others) to control Adafruit
 * NeoPixels, FLORA RGB Smart Pixels and compatible devices -- WS2811,
 * WS2812, WS2812B, SK6812, etc.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing products
 * from Adafruit!
 *
 * Written by Phil "Paint Your Dragon" Burgess for Adafruit Industries,
 * with contributions by PJRC, Michael Miller and other members of the
 * open source community.
 *
 * This file is part of the Adafruit_NeoPixel library.
 *
 * Adafruit_NeoPixel is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Adafruit_NeoPixel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with NeoPixel.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

// Modified version

#ifndef _ADAFRUIT_NEOPIXEL_H
#define _ADAFRUIT_NEOPIXEL_H

#include "wino.h"

// RGB NeoPixel permutations; white and red offsets are always same
// Offset:        W          R          G          B
#define NEO_RGB ((0 << 6) | (0 << 4) | (1 << 2) | (2)) ///< Transmit as R,G,B
#define NEO_RBG ((0 << 6) | (0 << 4) | (2 << 2) | (1)) ///< Transmit as R,B,G
#define NEO_GRB ((1 << 6) | (1 << 4) | (0 << 2) | (2)) ///< Transmit as G,R,B
#define NEO_GBR ((2 << 6) | (2 << 4) | (0 << 2) | (1)) ///< Transmit as G,B,R
#define NEO_BRG ((1 << 6) | (1 << 4) | (2 << 2) | (0)) ///< Transmit as B,R,G
#define NEO_BGR ((2 << 6) | (2 << 4) | (1 << 2) | (0)) ///< Transmit as B,G,R

// RGBW NeoPixel permutations; all 4 offsets are distinct
// Offset:         W          R          G          B
#define NEO_WRGB ((0 << 6) | (1 << 4) | (2 << 2) | (3)) ///< Transmit as W,R,G,B
#define NEO_WRBG ((0 << 6) | (1 << 4) | (3 << 2) | (2)) ///< Transmit as W,R,B,G
#define NEO_WGRB ((0 << 6) | (2 << 4) | (1 << 2) | (3)) ///< Transmit as W,G,R,B
#define NEO_WGBR ((0 << 6) | (3 << 4) | (1 << 2) | (2)) ///< Transmit as W,G,B,R
#define NEO_WBRG ((0 << 6) | (2 << 4) | (3 << 2) | (1)) ///< Transmit as W,B,R,G
#define NEO_WBGR ((0 << 6) | (3 << 4) | (2 << 2) | (1)) ///< Transmit as W,B,G,R

#define NEO_RWGB ((1 << 6) | (0 << 4) | (2 << 2) | (3)) ///< Transmit as R,W,G,B
#define NEO_RWBG ((1 << 6) | (0 << 4) | (3 << 2) | (2)) ///< Transmit as R,W,B,G
#define NEO_RGWB ((2 << 6) | (0 << 4) | (1 << 2) | (3)) ///< Transmit as R,G,W,B
#define NEO_RGBW ((3 << 6) | (0 << 4) | (1 << 2) | (2)) ///< Transmit as R,G,B,W
#define NEO_RBWG ((2 << 6) | (0 << 4) | (3 << 2) | (1)) ///< Transmit as R,B,W,G
#define NEO_RBGW ((3 << 6) | (0 << 4) | (2 << 2) | (1)) ///< Transmit as R,B,G,W

#define NEO_GWRB ((1 << 6) | (2 << 4) | (0 << 2) | (3)) ///< Transmit as G,W,R,B
#define NEO_GWBR ((1 << 6) | (3 << 4) | (0 << 2) | (2)) ///< Transmit as G,W,B,R
#define NEO_GRWB ((2 << 6) | (1 << 4) | (0 << 2) | (3)) ///< Transmit as G,R,W,B
#define NEO_GRBW ((3 << 6) | (1 << 4) | (0 << 2) | (2)) ///< Transmit as G,R,B,W
#define NEO_GBWR ((2 << 6) | (3 << 4) | (0 << 2) | (1)) ///< Transmit as G,B,W,R
#define NEO_GBRW ((3 << 6) | (2 << 4) | (0 << 2) | (1)) ///< Transmit as G,B,R,W

#define NEO_BWRG ((1 << 6) | (2 << 4) | (3 << 2) | (0)) ///< Transmit as B,W,R,G
#define NEO_BWGR ((1 << 6) | (3 << 4) | (2 << 2) | (0)) ///< Transmit as B,W,G,R
#define NEO_BRWG ((2 << 6) | (1 << 4) | (3 << 2) | (0)) ///< Transmit as B,R,W,G
#define NEO_BRGW ((3 << 6) | (1 << 4) | (2 << 2) | (0)) ///< Transmit as B,R,G,W
#define NEO_BGWR ((2 << 6) | (3 << 4) | (1 << 2) | (0)) ///< Transmit as B,G,W,R
#define NEO_BGRW ((3 << 6) | (2 << 4) | (1 << 2) | (0)) ///< Transmit as B,G,R,W

// Add NEO_KHZ400 to the color order value to indicate a 400 KHz device.
// All but the earliest v1 NeoPixels expect an 800 KHz data stream, this is
// the default if unspecified. Because flash space is very limited on ATtiny
// devices (e.g. Trinket, Gemma), v1 NeoPixels aren't handled by default on
// those chips, though it can be enabled by removing the ifndef/endif below,
// but code will be bigger. Conversely, can disable the NEO_KHZ400 line on
// other MCUs to remove v1 support and save a little space.

#define NEO_KHZ800 0x0000 ///< 800 KHz data transmission
#ifndef __AVR_ATtiny85__
#define NEO_KHZ400 0x0100 ///< 400 KHz data transmission
#endif

// If 400 KHz support is enabled, the third parameter to the constructor
// requires a 16-bit value (in order to select 400 vs 800 KHz speed).
// If only 800 KHz is enabled (as is default on ATtiny), an 8-bit value
// is sufficient to encode pixel color order, saving some space.

#ifdef NEO_KHZ400
typedef uint16_t neoPixelType; ///< 3rd arg to Adafruit_NeoPixel constructor
#else
typedef uint8_t neoPixelType; ///< 3rd arg to Adafruit_NeoPixel constructor
#endif

// [...] Two table removed from original

/* Declare external methods required by the Adafruit_NeoPixel implementation
    for specific hardware/library versions
*/
#if defined(ESP32)
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
extern "C" void espInit();
#endif
#endif

/*!
    @brief  Class that stores state and functions for interacting with
            Adafruit NeoPixels and compatible devices.
*/

#define ADAFRUIT_NEOPIXEL_MAXLEDS 256

class Adafruit_NeoPixel {
  uint8_t leds[ADAFRUIT_NEOPIXEL_MAXLEDS][4]; // rgbw
  uint16_t count, pin;
public:
  Adafruit_NeoPixel(uint16_t n, int16_t pin = 6, neoPixelType ignored = 0);

  bool begin(void);
  void show(void);
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

  inline void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) { setPixelColor(n, r, g, b, 0); }
  inline void setPixelColor(uint16_t n, uint32_t c) { setPixelColor(n, (c>>16)&0xff, (c>>8)&0xff, c&0xff, (c>>24)&0xff); }

  static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }
};

#endif
