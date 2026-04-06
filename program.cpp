#include <stdio.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define I2C_7SEG	0x71
#define I2C_LCD 	0x20

#define LCD_COLS 16

#define ROWS 4
#define COLS 4

#define KEYMAP "123A" "456B" "789C" "*0#D"

byte rows[] = {11, 10, 9, 8};
byte cols[] = { 7,  6, 5, 4};

Keypad keys(KEYMAP, rows, cols, ROWS, COLS);
LiquidCrystal_I2C lcd   (I2C_LCD , LCD_COLS, 2);
Adafruit_7segment floorN;
Adafruit_NeoPixel floors(10, 2, NEO_GRB + NEO_KHZ800);
int cur = 0;

void setup() {
  Serial.begin(9600);
  floors.begin();
  floorN.begin(I2C_7SEG);
  lcd.init();					
  lcd.backlight();
}

void loop() {
  char pressed = keys.getKey();

  if('0' <= pressed && pressed <= '9') {
	  char ligne[LCD_COLS+1];

  	floors.setPixelColor(cur, floors.Color(0, 0, 0));
    cur = pressed - '0';

    snprintf(ligne, LCD_COLS, "Floor: %d", cur);
    lcd.setCursor(0,0);
    lcd.print(ligne);    
    
    floors.setPixelColor(cur, floors.Color(255, 64, 0));
    floors.show();

    floorN.writeDigitNum(4, cur);
    floorN.writeDigitRaw(0, 1<<0);
    floorN.writeDigitRaw(1, 1<<6);
    floorN.writeDigitRaw(3, 1<<3);
    floorN.writeDisplay();
  }
}