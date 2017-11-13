/*
 * Control functions for timer.
 */

#include "ts.h"

/* Uptime counter
 * |--Day--|--Hour--|--Minute--|--Second--|--Ticks--|
 * 32      23       18         12         6         0
 */
static unsigned long uptime;

// Initialize timer's configuration registers
void initTimer() {
    TIM4_PSCR = 0x06;
    TIM4_IER = 0x01;    // Enable interrupt on update event
    TIM4_CR1 = 0x05;    // Enable timer
    resetUptime();
}

void resetUptime() {
    uptime = 0;
}

unsigned long getUptime() {
    return uptime;
}

unsigned char getUptimeSeconds() {
    return (unsigned char)((uptime >> 7) & 0x3F);
}

unsigned char getUptimeMinutes() {
    return (unsigned char)((uptime >> 13) & 0x3F);
}

unsigned char getUptimeHours() {
    return (unsigned char)((uptime >> 19) & 0x1F);
}

unsigned char getUptimeDays() {
    return (unsigned char)((uptime >> 24) & 0xFF);
}

/**
 * This function is interrupt request handler
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
    if (((unsigned char)uptime & 0x07) == 1) startADC();
    if (((unsigned char)uptime & 0x07) == 2) refreshMenu();
}
