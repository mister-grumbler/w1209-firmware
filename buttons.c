/**
 * Control functions for buttons.
 */

#include "ts.h"

static unsigned char status;
static unsigned char diff;

/**
 * @brief 
 */
void initButtons() {
    PC_CR1 |= BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT;
    PC_CR2 |= BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT;
    status = 0;
    diff = 0;
    EXTI_CR1 |= 0x30;   // generate interrupt on falling and rising front.
}

/**
 * @brief 
 * @return 
 */
unsigned char getButton() {
    return status;
}

/**
 * @brief 
 * @return 
 */
unsigned char getButtonDiff() {
    return diff;
}

/**
 * @brief 
 * @return 
 */
bool getButton1() {
    return status & BUTTON1_BIT;
}

/**
 * @brief 
 * @return 
 */
bool getButton2() {
    return status & BUTTON2_BIT;
}

/**
 * @brief 
 * @return 
 */
bool getButton3() {
    return status & BUTTON3_BIT;
}

/**
 * @brief 
 * @return 
 */
bool isButton1() {
    if (diff & BUTTON1_BIT) {
        diff &= ~BUTTON1_BIT;
        return true;
    }
    return false;
}

/**
 * @brief 
 * @return 
 */
bool isButton2() {
    if (diff & BUTTON2_BIT) {
        diff &= ~BUTTON2_BIT;
        return true;
    }
    return false;
}

/**
 * @brief 
 * @return 
 */
bool isButton3() {
    if (diff & BUTTON3_BIT) {
        diff &= ~BUTTON3_BIT;
        return true;
    }
    return false;
}

/**
 * @brief This function is button's interrupt request handler
 * so keep it extremely small and fast.
 */
void EXTI2_handler() __interrupt(5) {
    unsigned char event;
    diff = status ^ ~(PC_IDR & (BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT));
    status = ~(PC_IDR & (BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT));
    
    // Send appropriate event to menu.
    if (isButton1()) {
        if (getButton1()) {
            event = MENU_EVENT_PUSH_BUTTON1;
        } else {
            event = MENU_EVENT_RELEASE_BUTTON1;
        }
    } else if (isButton2()) {
        if (getButton2()) {
            event = MENU_EVENT_PUSH_BUTTON2;
        } else {
            event = MENU_EVENT_RELEASE_BUTTON2;
        }
    } else if (isButton3()) {
        if (getButton3()) {
            event = MENU_EVENT_PUSH_BUTTON3;
        } else {
            event = MENU_EVENT_RELEASE_BUTTON3;
        }
    } else {
        return;
    }
    feedMenu(event);
}
