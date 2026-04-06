#include "LiquidCrystal_I2C.h"

#include <emscripten/emscripten.h>

LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) :
  addr(lcd_Addr),
  cols(lcd_cols),
  x(0), y(0)
{
    for(int i=0; i<lcd_rows; i++) {
        lines.emplace_back(cols, ' ');
    }
} 

void LiquidCrystal_I2C::buildKeyName(char buf[], uint16_t cbuf) const {
    snprintf(buf, cbuf, "i2c/%d", addr);
}

void LiquidCrystal_I2C::write(uint8_t line) {
    EM_ASM(
        Module.Wino.byId($0)?.line?.($1, UTF8ToString($2)),
        getId(), line, lines[line].c_str()
    );
}

void LiquidCrystal_I2C::init () { }

void LiquidCrystal_I2C::clear() {
    for(int i=0; i<lines.size(); i++) {
        lines[i].assign(cols, ' ');
        write(i);
    }
    x=y=0;
} 
void LiquidCrystal_I2C::backlight()  {
    EM_ASM(Module.Wino.byId($0)?.backlight?.(), getId());
} 
void LiquidCrystal_I2C::setCursor(uint8_t x, uint8_t y) {
    if(x<cols && y<lines.size()) {
        this->x = x;
        this->y = y;
    }
} 
void LiquidCrystal_I2C::print(const char text[]) {
    const char *p = text;

    for(; y<lines.size() && *p; y++) {
        for(; x<cols && *p; x++) {
            lines[y][x] = *(p++);
        }
        write(y);
        if(x==cols) {
            x=0;
            y++;
        }
    }
    if(y==lines.size()) {
        y=0;
    }
}
