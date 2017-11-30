#ifndef MENU_H
#define MENU_H

/* Definitions for menu */
#define MENU_ROOT          0
#define MENU_SET_THRESHOLD 1
#define MENU_SELECT_PARAM  2
#define MENU_CHANGE_PARAM  3

#define MENU_EVENT_PUSH_BUTTON1     0
#define MENU_EVENT_PUSH_BUTTON2     1
#define MENU_EVENT_PUSH_BUTTON3     2
#define MENU_EVENT_RELEASE_BUTTON1  3
#define MENU_EVENT_RELEASE_BUTTON2  4
#define MENU_EVENT_RELEASE_BUTTON3  5
#define MENU_EVENT_CHECK_TIMER      6

void initMenu();
void feedMenu (unsigned char event);
void refreshMenu();
unsigned char getMenuDisplay();

#endif
