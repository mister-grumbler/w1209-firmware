/**
 * Implementation of application menu.
 */

#include "ts.h"

// TODO: these values should be corrected afterwards
// to correspond more precise to given time intervals.
#define MENU_AUTOINC_DELAY  1
#define MENU_1_SEC_PASSED   15
#define MENU_3_SEC_PASSED   45
#define MENU_5_SEC_PASSED   90

static unsigned char menuDisplay;
static unsigned char menuState;
static unsigned int timer;

/**
 * @brief Initialization of local variables.
 */
void initMenu()
{
    timer = 0;
    menuState = menuDisplay = MENU_ROOT;
}

/**
 * @brief Gets menu state for displaying appropriate value on the SSD.
 * @return
 */
unsigned char getMenuDisplay()
{
    return menuDisplay;
}

/**
 * @brief Updating state of application's menu and displaying info when new
 *  event is received. Possible states of menu and displaying are:
 *  MENU_ROOT
 *  MENU_SELECT_PARAM
 *  MENU_CHANGE_PARAM
 *  MENU_SET_THRESHOLD
 *
 * @param event is one of:
 *  MENU_EVENT_PUSH_BUTTON1
 *  MENU_EVENT_PUSH_BUTTON2
 *  MENU_EVENT_PUSH_BUTTON3
 *  MENU_EVENT_RELEASE_BUTTON1
 *  MENU_EVENT_RELEASE_BUTTON2
 *  MENU_EVENT_RELEASE_BUTTON3
 *  MENU_EVENT_CHECK_TIMER
 */
void feedMenu (unsigned char event)
{
    bool blink;

    if (menuState == MENU_ROOT) {
        switch (event) {
        case MENU_EVENT_PUSH_BUTTON1:
            timer = 0;
            menuDisplay = MENU_SET_THRESHOLD;
            break;

        case MENU_EVENT_RELEASE_BUTTON1:
            if (timer < MENU_5_SEC_PASSED) {
                menuState = MENU_SET_THRESHOLD;
            }

            timer = 0;
            break;

        case MENU_EVENT_CHECK_TIMER:
            if (getButton1() ) {
                if (timer > MENU_3_SEC_PASSED) {
                    setParamId (0);
                    timer = 0;
                    menuState = menuDisplay = MENU_SELECT_PARAM;
                }
            }

            break;

        default:
            if (timer > MENU_5_SEC_PASSED) {
                timer = 0;
                menuState = menuDisplay = MENU_ROOT;
            }

            break;
        }
    } else if (menuState == MENU_SELECT_PARAM) {
        // TODO: store into EEPROM on timeout and return to MENU_ROOT
        switch (event) {
        case MENU_EVENT_PUSH_BUTTON1:
            menuState = menuDisplay = MENU_CHANGE_PARAM;

        case MENU_EVENT_RELEASE_BUTTON1:
            timer = 0;
            break;

        case MENU_EVENT_PUSH_BUTTON2:
            incParamId();

        case MENU_EVENT_RELEASE_BUTTON2:
            timer = 0;
            break;

        case MENU_EVENT_PUSH_BUTTON3:
            decParamId();

        case MENU_EVENT_RELEASE_BUTTON3:
            timer = 0;
            break;

        case MENU_EVENT_CHECK_TIMER:
            if (timer > MENU_1_SEC_PASSED + MENU_AUTOINC_DELAY) {
                if (getButton2() ) {
                    incParamId();
                    timer = MENU_1_SEC_PASSED;
                } else if (getButton3() ) {
                    decParamId();
                    timer = MENU_1_SEC_PASSED;
                }
            }

            if (timer > MENU_5_SEC_PASSED) {
                timer = 0;
                setParamId (0);
                storeParams();
                menuState = menuDisplay = MENU_ROOT;
            }

            break;

        default:
            break;
        }
    } else if (menuState == MENU_CHANGE_PARAM) {
        // TODO: store into EEPROM on timeout and return to MENU_ROOT
        switch (event) {
        case MENU_EVENT_PUSH_BUTTON1:
            menuState = menuDisplay = MENU_SELECT_PARAM;

        case MENU_EVENT_RELEASE_BUTTON1:
            timer = 0;
            break;

        case MENU_EVENT_PUSH_BUTTON2:
            incParam();

        case MENU_EVENT_RELEASE_BUTTON2:
            timer = 0;
            break;

        case MENU_EVENT_PUSH_BUTTON3:
            decParam();

        case MENU_EVENT_RELEASE_BUTTON3:
            timer = 0;
            break;

        case MENU_EVENT_CHECK_TIMER:
            if (timer > MENU_1_SEC_PASSED + MENU_AUTOINC_DELAY) {
                if (getButton2() ) {
                    incParam();
                    timer = MENU_1_SEC_PASSED;
                } else if (getButton3() ) {
                    decParam();
                    timer = MENU_1_SEC_PASSED;
                }
            }

            if (getButton1() && timer > MENU_3_SEC_PASSED) {
                timer = 0;
                menuState = menuDisplay = MENU_SELECT_PARAM;
                break;
            }

            if (timer > MENU_5_SEC_PASSED) {
                timer = 0;
                storeParams();
                menuState = menuDisplay = MENU_ROOT;
            }

            break;

        default:
            break;
        }
    } else if (menuState == MENU_SET_THRESHOLD) {
        // TODO: on timeout store into EEPROM and return to MENU_ROOT
        switch (event) {
        case MENU_EVENT_PUSH_BUTTON1:
            timer = 0;
            menuDisplay = MENU_ROOT;
            setDisplayOff (false);
            break;

        case MENU_EVENT_RELEASE_BUTTON1:
            if (timer < MENU_5_SEC_PASSED) {
                storeParams();
                menuState = MENU_ROOT;
                setDisplayOff (false);
            }

            timer = 0;
            break;

        case MENU_EVENT_PUSH_BUTTON2:
            setParamId (PARAM_THRESHOLD);
            incParam();

        case MENU_EVENT_RELEASE_BUTTON2:
            timer = 0;
            break;

        case MENU_EVENT_PUSH_BUTTON3:
            setParamId (PARAM_THRESHOLD);
            decParam();

        case MENU_EVENT_RELEASE_BUTTON3:
            timer = 0;
            break;

        case MENU_EVENT_CHECK_TIMER:
            if (getButton2() || getButton3() ) {
                blink = false;
            } else {
                blink = (bool) (getUptime() & 0x40);
            }

            if (timer > MENU_1_SEC_PASSED + MENU_AUTOINC_DELAY) {
                setParamId (PARAM_THRESHOLD);

                if (getButton2() ) {
                    incParam();
                    timer = MENU_1_SEC_PASSED;
                } else if (getButton3() ) {
                    decParam();
                    timer = MENU_1_SEC_PASSED;
                }
            }

            setDisplayOff (blink);

            if (timer > MENU_5_SEC_PASSED) {
                timer = 0;

                if (getButton1() ) {
                    menuState = menuDisplay = MENU_SELECT_PARAM;
                    setDisplayOff (false);
                    break;
                }

                storeParams();
                menuState = menuDisplay = MENU_ROOT;
                setDisplayOff (false);
            }

            break;

        default:
            break;
        }
    }
}

/**
 * @brief This function is being called during timer's interrupt
 *  request so keep it extremely small and fast.
 *  During this call all time-related functionality of application
 *  menu is handled. For example: fast value change while holding
 *  a button, return to root menu when no action is received from
 *  user within a given time.
 */
void refreshMenu()
{
    timer++;
    feedMenu (MENU_EVENT_CHECK_TIMER);
}
