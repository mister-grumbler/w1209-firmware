#include "stm8l.h"

#define bool    _Bool
#define true    1
#define false   0

#define INTERRUPT_ENABLE    __asm rim __endasm;
#define INTERRUPT_DISABLE   __asm sim __endasm;
#define WAIT_FOR_INTERRUPT  __asm wfi __endasm;

/* Definitions for indicator */
// Port A controls segments: B, F
// 0000 0110
#define SSD_SEG_BF_PORT     PA_ODR
#define SSD_BF_PORT_MASK    0b00000110
// Port C controls segments: C, G
// 1100 0000
#define SSD_SEG_CG_PORT     PC_ODR
#define SSD_CG_PORT_MASK    0b11000000
// Port D controls segments: A, E, D, P
// 0010 1110
#define SSD_SEG_AEDP_PORT   PD_ODR
#define SSD_AEDP_PORT_MASK  0b00101110

// PD.5
#define SSD_SEG_A_BIT       0x20
// PA.2
#define SSD_SEG_B_BIT       0x04
// PC.7
#define SSD_SEG_C_BIT       0x80
// PD.3
#define SSD_SEG_D_BIT       0x08
// PD.1
#define SSD_SEG_E_BIT       0x02
// PA.1
#define SSD_SEG_F_BIT       0x02
// PC.6
#define SSD_SEG_G_BIT       0x40
// PD.2
#define SSD_SEG_P_BIT       0x04

// Port B controls digits: 1, 2
#define SSD_DIGIT_12_PORT   PB_ODR
// Port D controls digit: 3
#define SSD_DIGIT_3_PORT    PD_ODR

// PB.4
#define SSD_DIGIT_1_BIT     0x10
// PB.5
#define SSD_DIGIT_2_BIT     0x20
// PD.4
#define SSD_DIGIT_3_BIT     0x10

#define RELAY_PORT              PA_ODR
#define RELAY_BIT               0x08
#define RELAY_TIMER_MULTIPLIER  7

/* Definition for timer 4 (indicator refresh) */
// control register 1
#define TIM4_CR1    *(unsigned char*)0x5340
// interrupt enable register
#define TIM4_IER    *(unsigned char*)0x5343
// status register
#define TIM4_SR     *(unsigned char*)0x5344
// event generation register
#define TIM4_EGR    *(unsigned char*)0x5345
// counter register
#define TIM4_CNTR   *(unsigned char*)0x5346
// prescaler register
#define TIM4_PSCR   *(unsigned char*)0x5347
// auto-reload register
#define TIM4_ARR    *(unsigned char*)0x5348

/* Definition for external interrupts */
// control register 1
#define EXTI_CR1    *(unsigned char*)0x50A0
// control register 2
#define EXTI_CR2    *(unsigned char*)0x50A1

/* Definition for buttons */
// Port C control input from buttons.
#define BUTTONS_PORT   PC_IDR
// PC.3
#define BUTTON1_BIT    0x08
// PC.4
#define BUTTON2_BIT    0x10
// PC.5
#define BUTTON3_BIT    0x20

/* Definitions for ADC */
// 22 - ADC1 interrupt
// Port D.6 (pin 3) is used as analog input (AIN6)
#define ADC_CSR     *(unsigned char*)0x5400
#define ADC_CR1     *(unsigned char*)0x5401
#define ADC_CR2     *(unsigned char*)0x5402
#define ADC_CR3     *(unsigned char*)0x5403
#define ADC_DRH     *(unsigned char*)0x5404
#define ADC_DRL     *(unsigned char*)0x5405
#define ADC_TDRH    *(unsigned char*)0x5406
#define ADC_TDRL    *(unsigned char*)0x5407
#define ADC_HTRH    *(unsigned char*)0x5408
#define ADC_HTRL    *(unsigned char*)0x5409
#define ADC_LTRH    *(unsigned char*)0x540A
#define ADC_LTRL    *(unsigned char*)0x540B
#define ADC_AWSRH   *(unsigned char*)0x540C
#define ADC_AWSRL   *(unsigned char*)0x540D
#define ADC_AWCRH   *(unsigned char*)0x540E
#define ADC_AWCRL   *(unsigned char*)0x540F
// Averaging bits
#define ADC_AVERAGING_BITS  6

/* Definitions for EEPROM */
#define FLASH_DUKR                      *(unsigned char*)0x5064
#define FLASH_IAPSR                     *(unsigned char*)0x505F
#define EEPROM_BASE_ADDR                0x4000
#define EEPROM_PARAMS_OFFSET            100

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
void setDisplayOff(bool val);
void setDisplayTestMode(bool);
void setDisplayDot(unsigned char id, bool val);
void setDisplayStr(const unsigned char*);
void setDisplayInt(int);
void setDisplayUInt(unsigned int);
void setDisplayUIntHex(unsigned int);
void setDisplayUChar(unsigned char);
void setDisplayUCharHex(unsigned char);
void setDisplayUCharBCD(unsigned char);
void setDisplayUIntBCD(unsigned int);
void itofpa(int, unsigned char*, unsigned char);

void initTimer();
void resetUptime();
unsigned long getUptime();
unsigned char getUptimeSeconds();
unsigned char getUptimeMinutes();
unsigned char getUptimeHours();
unsigned char getUptimeDays();
void TIM4_UPD_handler() __interrupt(23);

void initButtons();
unsigned char getButton();
unsigned char getButtonDiff();
bool getButton1();
bool getButton2();
bool getButton3();
bool isButton1();
bool isButton2();
bool isButton3();
void EXTI2_handler() __interrupt(5);

void initADC();
void startADC();
unsigned int getAdcResult();
unsigned int getAdcAveraged();
int getTemperature();
void ADC1_EOC_handler() __interrupt(22);

void initParamsEEPROM();
int getParamById(unsigned char);
void setParamById(unsigned char, int);
int getParam();
void setParam(int);
void incParam();
void decParam();
unsigned char getParamId();
void setParamId(unsigned char);
void incParamId();
void decParamId();
void paramToString(unsigned char, unsigned char*);

void initMenu();
void feedMenu(unsigned char event);
void refreshMenu();
unsigned char getMenuDisplay();

void initRelay();
void setRelay(bool on);
void refreshRelay();