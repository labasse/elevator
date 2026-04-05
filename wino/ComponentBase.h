#ifndef _COMPONENTBASE_H
#define _COMPONENTBASE_H

#include "wino.h"

class ComponentBase {
public:
    ComponentBase();
    virtual ~ComponentBase() = default;

    const uint16_t MaxKeyNameSize = 256;
protected:
    int getId() const;
    
    virtual void buildKeyName(char buf[], uint16_t cbuf) const = 0;

public:
    mutable int id; // mutable: its a cache
};

#endif