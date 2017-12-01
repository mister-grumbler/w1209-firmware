#include "stm8l.h"
#include "adc.h"
#include "buttons.h"
#include "display.h"
#include "menu.h"
#include "params.h"
#include "relay.h"
#include "timer.h"

#define INTERRUPT_ENABLE    __asm rim __endasm;
#define INTERRUPT_DISABLE   __asm sim __endasm;
#define WAIT_FOR_INTERRUPT  __asm wfi __endasm;

/**
 * @brief
 */
int main()
{
    static unsigned char* stringBuffer[7];
    unsigned char paramMsg[] = {'P', '0', 0};

    initMenu();
    initButtons();
    initParamsEEPROM();
    initDisplay();
    initADC();
    initRelay();
    initTimer();

    INTERRUPT_ENABLE

    // Loop
    while (true) {
        if (getUptimeSeconds() > 0) {
            setDisplayTestMode (false);
        }

        if (getMenuDisplay() == MENU_ROOT) {
            int temp = getTemperature();
            itofpa (temp, (char*) stringBuffer, 0);
            setDisplayStr ( (char*) stringBuffer);

            if (getParamById (PARAM_OVERHEAT_INDICATION) ) {
                if (temp < getParamById (PARAM_MIN_TEMPERATURE) ) {
                    setDisplayStr ("LLL");
                } else if (temp > getParamById (PARAM_MAX_TEMPERATURE) ) {
                    setDisplayStr ("HHH");
                }
            }
        } else if (getMenuDisplay() == MENU_SET_THRESHOLD) {
            paramToString(PARAM_THRESHOLD, (char*) stringBuffer);
            setDisplayStr ((char*) stringBuffer);
        } else if (getMenuDisplay() == MENU_SELECT_PARAM) {
            paramMsg[1] = '0' + getParamId();
            setDisplayStr ( (unsigned char*) &paramMsg);
        } else if (getMenuDisplay() == MENU_CHANGE_PARAM) {
            paramToString (getParamId(), (char*) stringBuffer);
            setDisplayStr ( (char *) stringBuffer);
        } else {
            setDisplayStr ("ERR");
            setDisplayOff ( (bool) (getUptime() & 0x40) );
        }

        WAIT_FOR_INTERRUPT
    };
}
