#ifndef TIMER_H
#define TIMER_H

void initTimer();
void resetUptime();
unsigned long getUptime();
unsigned char getUptimeSeconds();
unsigned char getUptimeMinutes();
unsigned char getUptimeHours();
unsigned char getUptimeDays();
void TIM4_UPD_handler() __interrupt (23);

#endif