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
    initTimer();
    initButtons();
    initADC();
    initRelay();

    INTERRUPT_ENABLE
    // Loop
    do {
        if (getUptimeSeconds() > 0) setDisplayTestMode(false);
        if (getMenuDisplay() == MENU_ROOT) {
            setDisplayUInt(getAdcAveraged() >> 4); // todo: see issue #1 and #2
            setDisplayOff(false);
        } else if (getMenuDisplay() == MENU_SET_THRESHOLD) {
            setDisplayUInt(getParamById(PARAM_THRESHOLD));
            setDisplayOff((bool)(getUptime() & 0x40));
        } else if (getMenuDisplay() == MENU_SELECT_PARAM) {
            paramMsg[1] = '0' + getParamId();
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
