/*
 * This file is part of the W1209 firmware replacement project
 * (https://github.com/mister-grumbler/w1209-firmware).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Control functions for buttons.
 * The EXTI2 interrupt (5) is used to get signal on changing buttons state.
 */

#include "buttons.h"
#include "stm8s003/gpio.h"
#include "menu.h"

/* Definition for buttons */
// Port C control input from buttons.
#define BUTTONS_PORT   PC_IDR
// PC.3
#define BUTTON1_BIT    0x08
// PC.4
#define BUTTON2_BIT    0x10
// PC.5
#define BUTTON3_BIT    0x20

static unsigned char status;
static unsigned char diff;

/**
 * @brief Configure approptiate pins of MCU as digital inputs. Set
 *  initial value of status by getting current state of buttons.
 *  Configure external interrupt for these inputs.
 */
void initButtons()
{
    PC_CR1 |= BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT;
    PC_CR2 |= BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT;
    status = ~ (BUTTONS_PORT & (BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT) );
    diff = 0;
    EXTI_CR1 |= 0x30;   // generate interrupt on falling and rising front.
}

/**
 * @brief Gets value of buttons status which was when last interrupt
 *  request being handled.
 * @return status byte of buttons
 */
unsigned char getButton()
{
    return status;
}

/**
 * @brief
 * @return
 */
unsigned char getButtonDiff()
{
    return diff;
}

/**
 * @brief
 * @return
 */
bool getButton1()
{
    return status & BUTTON1_BIT;
}

/**
 * @brief
 * @return
 */
bool getButton2()
{
    return status & BUTTON2_BIT;
}

/**
 * @brief
 * @return
 */
bool getButton3()
{
    return status & BUTTON3_BIT;
}

/**
 * @brief
 * @return
 */
bool isButton1()
{
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
bool isButton2()
{
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
bool isButton3()
{
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
void EXTI2_handler() __interrupt (5)
{
    unsigned char event;
    diff = status ^ ~ (BUTTONS_PORT & (BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT) );
    status = ~ (BUTTONS_PORT & (BUTTON1_BIT | BUTTON2_BIT | BUTTON3_BIT) );

    // Send appropriate event to menu.
    if (isButton1() ) {
        if (getButton1() ) {
            event = MENU_EVENT_PUSH_BUTTON1;
        } else {
            event = MENU_EVENT_RELEASE_BUTTON1;
        }
    } else if (isButton2() ) {
        if (getButton2() ) {
            event = MENU_EVENT_PUSH_BUTTON2;
        } else {
            event = MENU_EVENT_RELEASE_BUTTON2;
        }
    } else if (isButton3() ) {
        if (getButton3() ) {
            event = MENU_EVENT_PUSH_BUTTON3;
        } else {
            event = MENU_EVENT_RELEASE_BUTTON3;
        }
    } else {
        return;
    }

    feedMenu (event);
}
