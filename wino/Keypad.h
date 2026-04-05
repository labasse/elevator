#ifndef _KEYPAD_H
#define _KEYPAD_H

#include <string>

#include "ComponentBase.h"

class Keypad : public ComponentBase {
public:
	Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);  

	char getKey();
	bool isPressed(char keyChar);
protected:
	void buildKeyName(char buf[], uint16_t cbuf) const override;
private:
	std::string keys, keyName;
    int keyMax;
};

#endif
