#include "ComponentBase.h"

#include <cstring>
#include <emscripten/emscripten.h>

ComponentBase::ComponentBase() : 
    id(-1) 
{ } 

int ComponentBase::getId() const {
    if(id < 0) {
        char buf[MaxKeyNameSize];

        buildKeyName(buf, MaxKeyNameSize);
        buf[MaxKeyNameSize-1] = '\0';
        id = EM_ASM_INT({
            const id = UTF8ToString($0);
            const res = Module.Wino?.idOf(id);

            if(res!==undefined) {
                return res
            }
            console.warn("Missing component " + id + " in the JS circuit");
            return -1
        }, buf);
    }
    return id;
}
