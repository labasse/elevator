#ifndef _LIQUIDCRYSTAL_I2C_H
#define _LIQUIDCRYSTAL_I2C_H

#include <vector>
#include <string>

#include "ComponentBase.h"

class LiquidCrystal_I2C : public ComponentBase {
public:
  LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
  
  void init ();
  void clear();
  void backlight();  
  void setCursor(uint8_t, uint8_t); 
  void print(const char[]);
protected:
  void buildKeyName(char buf[], uint16_t cbuf) const override;
private:
  void write(uint8_t line);

  std::vector<std::string> lines;
  uint8_t addr;
  uint8_t cols;
  uint8_t x, y;
};

#endif