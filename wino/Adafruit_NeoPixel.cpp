#include <emscripten/emscripten.h>

#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, int16_t pin, neoPixelType ignored) :
    leds{0},
    count(n),
    pin(pin)  
{ 
}

bool Adafruit_NeoPixel::begin() {
    auto ok = EM_ASM_INT({
        if(Module.Adafruit_NeoPixel[$0] === undefined) {
            console.warn("Pin " + $0 + " not connected to NeoPixels");
            return 0
        }
        return 1
    }, pin);
    if(ok)
        show();
    return ok;
}

void Adafruit_NeoPixel::show(void) {
    for(int i = 0; i<count; i++) {
        EM_ASM(
            Module.Adafruit_NeoPixel?.[$0]?.setColor($1, $2, $3, $4, $5),
            pin, i, leds[i][0], leds[i][1], leds[i][2], leds[i][3]
        );
    }
}

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    if(n < count) {
        leds[n][0] = r;
        leds[n][1] = g;
        leds[n][2] = b;
        leds[n][3] = w;
    }
}
