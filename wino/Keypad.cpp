#include "Keypad.h"

#include <cstdio>
#include <cstring>
#include <cassert>
#include <emscripten/emscripten.h>

static void stringify(char* dest, int max, byte *vals, byte nvals) {
    const char *sep = "";
    
    for(int i=0; i<nvals; i++) {
        for(; *dest; dest++, max--)
            ;
        snprintf(dest, max, "%s%d", sep, vals[i]);
        sep=",";
    }
}

Keypad::Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols) {
    int max = 4*(numRows+numCols)+5;
    char buf[max];
    
    strncpy(buf, "[[", max); 
    stringify(buf, max, row, numRows);
    strncat(buf, "],[", max);
    stringify(buf, max, col, numRows);
    strncat(buf, "]]", max);

    keyMax = numRows * numCols;
    assert(strlen(userKeymap) >= keyMax);
    keys = strdup(userKeymap);
    id = strdup(buf);
}

Keypad::Keypad(const Keypad& other) {
    keyMax = other.keyMax;
    keys = strdup(other.keys);
    id = strdup(other.id);
} 

Keypad::~Keypad() {
    free(keys);
    free(id);
}

bool Keypad::plugged() {
    return EM_ASM_INT({
        const id = UTF8ToString($0);
        if(Module.Keypad[id] === undefined) {
            console.warn("No Keypad plugged on "+id);
            return 0
        }
        return 1;
    }, id) == 1;
}

char Keypad::getKey() {
    char key = '\0';

    if(plugged()) {
        auto index = EM_ASM_INT({
            return Module.Keypad?.[UTF8ToString($0)]?.getPressedKeyIndex() ?? $1
        }, id, keyMax);
        if(index < keyMax)
            key = keys[index];
    }
    return key;
}

bool Keypad::isPressed(char keyChar) {
    return getKey() == keyChar;
}
