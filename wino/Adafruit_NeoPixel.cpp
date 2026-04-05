#include <emscripten/emscripten.h>
#include <cstdio>

#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, int16_t pin, neoPixelType ignored) :
    leds{0},
    count(n),
    pin(pin)  
{ }

void Adafruit_NeoPixel::buildKeyName(char buf[], uint16_t cbuf) const {
    snprintf(buf, cbuf, "Adafruit_NeoPixel/%d", pin);
}

bool Adafruit_NeoPixel::show(const char *warn) {
    auto id = getId();

    if(id < 0) {
        return false;
    }
    for(int i = 0; i<count; i++) {
        EM_ASM(
            Module.Wino.byId($0).setColor($1, $2, $3, $4, $5),
            getId(), i, leds[i][0], leds[i][1], leds[i][2], leds[i][3]
        );
    }
    return true;
}

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    if(n < count) {
        leds[n][0] = r;
        leds[n][1] = g;
        leds[n][2] = b;
        leds[n][3] = w;
    }
}
