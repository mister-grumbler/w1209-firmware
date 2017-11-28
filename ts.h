#include "stm8l.h"

#define bool    _Bool
#define true    1
#define false   0

#define INTERRUPT_ENABLE    __asm rim __endasm;
#define INTERRUPT_DISABLE   __asm sim __endasm;
#define WAIT_FOR_INTERRUPT  __asm wfi __endasm;

/* Definition for parameters */
#define PARAM_RELAY_MODE                0
#define PARAM_RELAY_HYSTERESIS          1
#define PARAM_MAX_TEMPERATURE           2
#define PARAM_MIN_TEMPERATURE           3
#define PARAM_TEMPERATURE_CORRECTION    4
#define PARAM_RELAY_DELAY               5
#define PARAM_OVERHEAT_INDICATION       6
#define PARAM_THRESHOLD                 9

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

void initIndicator();
void refreshDisplay();
void setDisplayOff (bool val);
void setDisplayTestMode (bool);
void setDisplayDot (unsigned char id, bool val);
void setDisplayStr (const unsigned char*);
void setDisplayInt (int);
void setDisplayUInt (unsigned int);
void setDisplayUIntHex (unsigned int);
void setDisplayUChar (unsigned char);
void setDisplayUCharHex (unsigned char);
void setDisplayUCharBCD (unsigned char);
void setDisplayUIntBCD (unsigned int);
void itofpa (int, unsigned char*, unsigned char);

void initTimer();
void resetUptime();
unsigned long getUptime();
unsigned char getUptimeSeconds();
unsigned char getUptimeMinutes();
unsigned char getUptimeHours();
unsigned char getUptimeDays();
void TIM4_UPD_handler() __interrupt (23);

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

void initADC();
void startADC();
unsigned int getAdcResult();
unsigned int getAdcAveraged();
int getTemperature();
void ADC1_EOC_handler() __interrupt (22);

void initParamsEEPROM();
int getParamById (unsigned char);
void setParamById (unsigned char, int);
int getParam();
void setParam (int);
void incParam();
void decParam();
unsigned char getParamId();
void setParamId (unsigned char);
void incParamId();
void decParamId();
void paramToString (unsigned char, unsigned char*);
void storeParams();

void initMenu();
void feedMenu (unsigned char event);
void refreshMenu();
unsigned char getMenuDisplay();

void initRelay();
void setRelay (bool on);
void refreshRelay();
