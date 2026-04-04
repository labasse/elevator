#include <stdio.h>
#include <Adafruit_NeoPixel.h>
#include <Keypad.h>

#define I2C_7SEG	0x70
#define I2C_LCD 	0x20

#define LCD_COLS 16

#define ROWS 4
#define COLS 4

#define KEYMAP "123A" "456B" "789C" "*0#D"

byte rows[] = {11, 10, 9, 8};
byte cols[] = { 7,  6, 5, 4};

Keypad keys(KEYMAP, rows, cols, ROWS, COLS); 
Adafruit_NeoPixel floors(10, 2, NEO_GRB + NEO_KHZ800);
int cur = 0;

void setup() {
  Serial.begin(9600);
  floors.begin();
}

void loop() {
  char pressed = keys.getKey();

  if('0' <= pressed && pressed <= '9') {
	  char ligne[LCD_COLS+1];

  	floors.setPixelColor(cur, floors.Color(0, 0, 0));
    cur = pressed - '0';
  	snprintf(ligne, LCD_COLS, "Floor: %d", cur);
    
    floors.setPixelColor(cur, floors.Color(255, 64, 0));
    floors.show();
  }
}