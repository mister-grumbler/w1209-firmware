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

#ifndef TIMER_H
#define TIMER_H

void initTimer();
void resetUptime();
unsigned long getUptime();
unsigned int getUptimeTicks();
unsigned char getUptimeSeconds();
unsigned char getUptimeMinutes();
unsigned char getUptimeHours();
unsigned char getUptimeDays();
void TIM4_UPD_handler() __interrupt (23);

#endif
