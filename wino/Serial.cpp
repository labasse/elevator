#include "Serial.h"

#include <emscripten/emscripten.h>

SerialType Serial;

void SerialType::begin(int baud) {
    enabled = true;    
}

void SerialType::end() {
    enabled = false;
}

void SerialType::println(const char *msg) const {
    if(enabled) EM_ASM(console.log(UTF8ToString($0)), msg);
}

void SerialType::println(uint8_t val) const {
    if(enabled) EM_ASM(console.log($0), val);
}
void SerialType::println(uint16_t val) const {
    if(enabled) EM_ASM(console.log($0), val);
}
void SerialType::println(uint32_t val) const {
    if(enabled) EM_ASM(console.log($0), val);
}

void SerialType::println(int8_t val) const {
    if(enabled) EM_ASM(console.log($0), val);
}
void SerialType::println(int16_t val) const {
    if(enabled) EM_ASM(console.log($0), val);
}
void SerialType::println(int32_t val) const {
    if(enabled) EM_ASM(console.log($0), val);
}
