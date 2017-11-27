#include "ts.h"

/**
 * @brief 
 */
int main() {
    static unsigned char* stringBuffer[7];
    unsigned char paramMsg[] = {'P','0',0};

    initMenu();
    initButtons();
    initParamsEEPROM();
    initIndicator();
    initADC();
    initRelay();
    initTimer();

    INTERRUPT_ENABLE
    // Loop
    do {
        if (getUptimeSeconds() > 0) setDisplayTestMode(false);
        if (getMenuDisplay() == MENU_ROOT) {
            int temp = getTemperature();
            setDisplayInt(temp); // todo: see issue #1 and #2
            if (getParamById(PARAM_OVERHEAT_INDICATION)) {
                if (temp < getParamById(PARAM_MIN_TEMPERATURE)) {
                    setDisplayStr("LLL");
                } else if (temp > getParamById(PARAM_MAX_TEMPERATURE)) {
                    setDisplayStr("HHH");
                }
            }
        } else if (getMenuDisplay() == MENU_SET_THRESHOLD) {
            setDisplayInt(getParamById(PARAM_THRESHOLD));
        } else if (getMenuDisplay() == MENU_SELECT_PARAM) {
            paramMsg[1] = '0' + getParamId();
            setDisplayStr((unsigned char*)&paramMsg);
        } else if (getMenuDisplay() == MENU_CHANGE_PARAM) {
            paramToString(getParamId(), (char*)stringBuffer);
            setDisplayStr((char *)stringBuffer);
        } else {
            setDisplayStr("ERR");
            setDisplayOff((bool)(getUptime() & 0x40));
        }

        WAIT_FOR_INTERRUPT
    } while(true);
}
