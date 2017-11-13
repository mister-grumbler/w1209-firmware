#include "ts.h"

const unsigned char* errMsg = "ERR";
unsigned char paramMsg[] = {' ','P','0',0};

/**
 * @brief TODO: move this functionality into appropriate place.
 */
void gpioInit(void) {
    // Configure system clock
//    CLK_DIVR = 0x00;    // Set the frequency to 16 MHz
//    CLK_PCKENR1 = 0xFF; // Enable peripherals

    // Configure pins
    // relay PA.3
    PA_DDR = 0x0E;
    PA_CR1 = 0x0E;
    return;
}

/**
 * @brief Converts integer value to BCD format.
 * Used to prepare a value to be shown on SSDisplay.
 * TODO: this function should be moved somewhere else.
 * @param val
 *  The value to be converted
 * @return value in BCD format.
 */
unsigned int uInt2BCD(unsigned int val) {
    unsigned int result = 0;
    signed char a;

    for(a = 13; a >= 0; a--){
        if((result & 0xF) >= 5)
            result += 3;
        if(((result & 0xF0) >> 4) >= 5)
            result += (3 << 4);
        if(((result & 0xF00) >> 8) >= 5)
            result += (3 << 8);
        result = (result << 1) | ((val >> a) & 1);
    }
    return result;
}

/**
 * @brief 
 */
int main() {
    int d,c;
    unsigned char param = 0;
    gpioInit();
    initParamsEEPROM();
    initIndicator();
    initTimer();
    initButtons();
    initADC();

    INTERRUPT_ENABLE
    // Loop
    do {
//        RELAY_PORT ^= RELAY_BIT; //toggle LED
        if (getUptimeSeconds() > 0) setDisplayTestMode(false);
        if (getMenuDisplay() == MENU_ROOT) {
            setDisplayUInt(getAdcAveraged());
            setDisplayOff(false);
        } else if (getMenuDisplay() == MENU_SET_THRESHOLD) {
            setDisplayUInt(getParamById(EEPROM_PARAM_THRESHOLD));
            setDisplayOff((bool)(getUptime() & 0x40));
        } else if (getMenuDisplay() == MENU_SELECT_PARAM) {
            paramMsg[2] = '0' + getParamId();
            setDisplayStr((unsigned char*)&paramMsg);
            setDisplayOff(false);
        } else if (getMenuDisplay() == MENU_CHANGE_PARAM) {
            setDisplayUCharHex(getParam());
            setDisplayOff(false);
        } else {
            setDisplayStr(errMsg);
            setDisplayOff((bool)(getUptime() & 0x40));
        }
        for(c = 0; c<10; c++)
        {
            for(d = 0; d<9900; d++);
        }
        WAIT_FOR_INTERRUPT
    } while(true);

}
