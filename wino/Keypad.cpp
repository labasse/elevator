#include "Keypad.h"

#include <cstdio>
#include <cassert>
#include <sstream>
#include <emscripten/emscripten.h>

static std::ostringstream& stringify(std::ostringstream& dest, byte *vals, byte nvals) {
    const char *sep = "";
    
    for(int i=0; i<nvals; i++) {
        dest << sep << (int)vals[i];
        sep=",";
    }
    return dest;
}

Keypad::Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols) :
    keyMax(numRows * numCols),
    keys (userKeymap)
{
    std::ostringstream s;
    
    s << "Keypad/[[";
    stringify(s, row, numRows) << "],[";
    stringify(s, col, numCols) << "]]";
    keyName = s.str();
    assert(keys.size() >= keyMax);
}

void Keypad::buildKeyName(char buf[], uint16_t cbuf) const {
    keyName.copy(buf, cbuf);
}

char Keypad::getKey() {
    auto key = '\0';
    auto index = EM_ASM_INT({
        return Module.Wino?.byId($0)?.getPressedKeyIndex() ?? $1
    }, getId(), keyMax);
    if(index < keyMax)
        key = keys[index];
    return key;
}

bool Keypad::isPressed(char keyChar) {
    return getKey() == keyChar;
}
