#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>

class SerialType
{
public:
    void begin(int baud);
    void end();

    void println(const char *msg) const;
    
    void println(uint8_t val) const;
    void println(uint16_t val) const;
    void println(uint32_t val) const;
    
    void println(int8_t val) const;
    void println(int16_t val) const;
    void println(int32_t val) const;
    
    void println(float val) const;
    void println(double val) const;
private:
    bool enabled = false;
};

extern SerialType Serial;

#endif