#ifndef BUTTONS_H
#define BUTTONS_H

#ifndef BOOL_TYPEDEF
#define bool    _Bool
#define true    1
#define false   0
#endif

void initButtons();
unsigned char getButton();
unsigned char getButtonDiff();
bool getButton1();
bool getButton2();
bool getButton3();
bool isButton1();
bool isButton2();
bool isButton3();
void EXTI2_handler() __interrupt (5);
#endif