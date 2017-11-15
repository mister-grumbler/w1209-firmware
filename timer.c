/**
 * Control functions for timer.
 */

#include "ts.h"

/**
 * Uptime counter
 * |--Day--|--Hour--|--Minute--|--Second--|--Ticks--|
 * 32      23       18         12         6         0
 */
static unsigned long uptime;

/**
 * @brief Initialize timer's configuration registers
 */
void initTimer() {
    TIM4_PSCR = 0x06;
    TIM4_IER = 0x01;    // Enable interrupt on update event
    TIM4_CR1 = 0x05;    // Enable timer
    resetUptime();
}

/**
 * @brief Sets value of uptime counter to zero.
 */
void resetUptime() {
    uptime = 0;
}

/**
 * @brief Gets raw value of bit-mapped uptime counter.
 * |--Day--|--Hour--|--Minute--|--Second--|--Ticks--|
 * 32      23       18         12         6         0
 * @return value of uptime counter.
 */
unsigned long getUptime() {
    return uptime;
}

/**
 * @brief Gets seconds part of time being passed since last reset.
 * @return seconds part of uptime.
 */
unsigned char getUptimeSeconds() {
    return (unsigned char)((uptime >> 7) & 0x3F);
}

/**
 * @brief Gets minutes part of time being passed since last reset.
 * @return minutes part of uptime.
 */
unsigned char getUptimeMinutes() {
    return (unsigned char)((uptime >> 13) & 0x3F);
}

/**
 * @brief Gets hours part of time being passed since last reset.
 * @return hours part of uptime.
 */
unsigned char getUptimeHours() {
    return (unsigned char)((uptime >> 19) & 0x1F);
}

/**
 * @brief Gets amount of days being passed since last reset.
 * @return amount of days.
 */
unsigned char getUptimeDays() {
    return (unsigned char)((uptime >> 24) & 0xFF);
}

/**
 * @brief This function is timer's interrupt request handler
 * so keep it extremely small and fast.
 */
void TIM4_UPD_handler() __interrupt(23) {
    TIM4_SR &= ~TIM_SR1_UIF; // Reset flag
    uptime++;
    // Increment minutes count when 60 seconds have passed.
    if(((unsigned char)(uptime >> 7) & 0x3F) == 0x3C) { // 60 seconds
        uptime &= ~0x1EFF;
        uptime += (unsigned long)1 << 13;
    }
    // Increment hours count when 60 minutes have passed.
    if(((unsigned char)(uptime >> 13) & 0x3F) == 0x3C) { // 60 minutes
        uptime &= ~0x7FFFF;
        uptime += (unsigned long)1 << 19;
    }
    // Increment days count when 24 hours have passed.
    if(((unsigned char)(uptime >> 19) & 0x1F) == 0x18) { // 24 hours
        uptime &= ~0xFFFFFF;
        uptime += (unsigned long)1 << 24;
    }
    refreshDisplay();
    if (((unsigned char)uptime & 0x07) == 1) refreshMenu();
    if (((unsigned char)uptime & 0x3F) == 2) startADC();
}
