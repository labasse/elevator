#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "wino.h"

class Keypad {
public:
	Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);  
	Keypad(const Keypad& other);  
	virtual ~Keypad();  

	char getKey();
	bool isPressed(char keyChar);
private:
	bool plugged();

    char *keys;
	char *id;
    int keyMax;
};

#endif
