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
 * Control functions for timer.
 * The TIM4 interrupt (23) is used to get signal on update event.
 */

#include "timer.h"
#include "stm8s003/clock.h"
#include "stm8s003/timer.h"
#include "adc.h"
#include "display.h"
#include "menu.h"
#include "relay.h"

#define TICK_PRESCALE_VALUE 3

/**
 * Uptime counter
 * |--Day--|--Hour--|--Minute--|--Second--|--Ticks--|
 * 32      23       18         12         6         0
 */
static unsigned long uptime;
static unsigned char tickPrescaler;

/**
 * @brief Initialize timer's configuration registers and reset uptime.
 */
void initTimer()
{
    CLK_CKDIVR = 0x00;    // Set the frequency to 16 MHz
    TIM4_PSCR = 0x07;
    TIM4_IER = 0x01;    // Enable interrupt on update event
    TIM4_CR1 = 0x05;    // Enable timer
    resetUptime();
}

/**
 * @brief Sets value of uptime counter to zero.
 */
void resetUptime()
{
    tickPrescaler = 0;
    uptime = 0;
}

/**
 * @brief Gets raw value of bit-mapped uptime counter.
 * |--Day--|--Hour--|--Minute--|--Second--|--Ticks--|
 * 32      23       18         12         6         0
 * @return value of uptime counter.
 */
unsigned long getUptime()
{
    return uptime;
}

/**
 * @brief Gets seconds part of time being passed since last reset.
 * @return seconds part of uptime.
 */
unsigned char getUptimeSeconds()
{
    return (unsigned char) ( (uptime >> 7) & 0x3F);
}

/**
 * @brief Gets minutes part of time being passed since last reset.
 * @return minutes part of uptime.
 */
unsigned char getUptimeMinutes()
{
    return (unsigned char) ( (uptime >> 13) & 0x3F);
}

/**
 * @brief Gets hours part of time being passed since last reset.
 * @return hours part of uptime.
 */
unsigned char getUptimeHours()
{
    return (unsigned char) ( (uptime >> 19) & 0x1F);
}

/**
 * @brief Gets amount of days being passed since last reset.
 * @return amount of days.
 */
unsigned char getUptimeDays()
{
    return (unsigned char) ( (uptime >> 24) & 0xFF);
}

/**
 * @brief This function is timer's interrupt request handler
 * so keep it small and fast as much as possible.
 */
void TIM4_UPD_handler() __interrupt (23)
{
    TIM4_SR &= ~TIM_SR1_UIF; // Reset flag
    tickPrescaler++;

    if (tickPrescaler < TICK_PRESCALE_VALUE) {
        return;
    }

    tickPrescaler = 0;
    uptime++;

    // Increment minutes count when 60 seconds have passed.
    if ( ( (unsigned char) (uptime >> 7) & 0x3F) == 0x3C) { // 60 seconds
        uptime &= ~0x1EFF;
        uptime += (unsigned long) 1 << 13;
    }

    // Increment hours count when 60 minutes have passed.
    if ( ( (unsigned char) (uptime >> 13) & 0x3F) == 0x3C) { // 60 minutes
        uptime &= ~0x7FFFF;
        uptime += (unsigned long) 1 << 19;
    }

    // Increment days count when 24 hours have passed.
    if ( ( (unsigned char) (uptime >> 19) & 0x1F) == 0x18) { // 24 hours
        uptime &= ~0xFFFFFF;
        uptime += (unsigned long) 1 << 24;
    }

    // Try not to call all refresh functions at once.
    refreshDisplay();

    if ( ( (unsigned char) uptime & 0x07) == 1) {
        refreshMenu();
    }

    if ( ( (unsigned char) uptime & 0x3F) == 2) {
        startADC();
    }

    if ( ( (unsigned char) uptime & 0x3F) == 3) {
        refreshRelay();
    }
}
