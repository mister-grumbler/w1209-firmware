#include "ts.h"


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
 * @brief 
 */
int main() {
    const unsigned char* errMsg = "ERR";
    unsigned char paramMsg[] = {' ','P','0',0};
    unsigned char param = 0;
    int d;

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
            setDisplayUInt(getParam());
            setDisplayOff(false);
        } else {
            setDisplayStr(errMsg);
            setDisplayOff((bool)(getUptime() & 0x40));
        }
        for(d = 0; d<9900; d++);
        WAIT_FOR_INTERRUPT
    } while(true);

}
