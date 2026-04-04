#include "wino.h"

#include <emscripten/emscripten.h>

extern void setup();
extern void loop ();

static double start;

extern "C" {
    void wino_setup() { 
        EM_ASM(Module); 
        start = emscripten_get_now();
        setup(); 
    }
    void wino_loop () { 
        loop (); 
    }
}

static bool _isValidPin(uint8_t pin) {
    return pin < NUM_DIGITAL_PINS;
}

void pinMode(uint8_t pin, uint8_t mode) {
    EM_ASM(Wino._c_pinMode(Module, $0, $1), pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t val) {
    if(_isValidPin(pin)) EM_ASM(Module.wino.io[$0] = val, pin);
}

int digitalRead(uint8_t pin) {
    return _isValidPin(pin) ? EM_ASM_INT(Module.wino.io[$0], pin) : 0;
}

int analogRead(uint8_t pin) {
    return _isValidPin(pin) ? EM_ASM_INT(Module.wino.io[$0], pin) : 0;
}
void analogReference(uint8_t mode) {

}
void analogWrite(uint8_t pin, int val) {
    if(_isValidPin(pin)) EM_ASM(Module.io[$0] = $1, pin, val);
}

unsigned long millis(void) {
    return (unsigned long)(emscripten_get_now() - start);
}
unsigned long micros(void) {
    return (long)((emscripten_get_now() - start)*1000.);
}
void delay(unsigned long ms) {
    emscripten_sleep(ms);
}
void delayMicroseconds(unsigned int us) {
    emscripten_sleep(us*1000);
}

long random(long max) {
    return random(0, max);
}
long random(long min, long max) {
    return min + rand() % (max-min);
}
void randomSeed(unsigned long seed) {
    srand(seed);
}
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh) {
    return toLow + ((value - fromLow) * (toHigh - toLow)) / (fromHigh - fromLow);
}
