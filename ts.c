#include "ts.h"


/**
 * @brief TODO: move this functionality into appropriate place.
 */
void gpioInit(void) {

    return;
}

/**
 * @brief 
 */
int main() {
    const unsigned char* errMsg = "ERR";
    unsigned char paramMsg[] = {'P','0',0};
    unsigned char param = 0;
    int d;

    initMenu();
    initParamsEEPROM();
    initIndicator();
    initButtons();
    initADC();
    initRelay();
    initTimer();

    INTERRUPT_ENABLE
    // Loop
    do {
        if (getUptimeSeconds() > 0) setDisplayTestMode(false);
        if (getMenuDisplay() == MENU_ROOT) {
            setDisplayInt(getTemperature()); // todo: see issue #1 and #2
            setDisplayOff(false);
        } else if (getMenuDisplay() == MENU_SET_THRESHOLD) {
            setDisplayInt(getParamById(PARAM_THRESHOLD));
        } else if (getMenuDisplay() == MENU_SELECT_PARAM) {
            paramMsg[1] = '0' + getParamId();
            setDisplayStr((unsigned char*)&paramMsg);
            setDisplayOff(false);
        } else if (getMenuDisplay() == MENU_CHANGE_PARAM) {
            setDisplayInt(getParam());
            setDisplayOff(false);
        } else {
            setDisplayStr(errMsg);
            setDisplayOff((bool)(getUptime() & 0x40));
        }
        for(d = 0; d<9900; d++);
        WAIT_FOR_INTERRUPT
    } while(true);

}
