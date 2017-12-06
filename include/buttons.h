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

#ifndef BUTTONS_H
#define BUTTONS_H

#ifndef bool
#define bool    _Bool
#define true    1
#define false   0
#endif

void initButtons();
bool isButton1();
bool isButton2();
bool isButton3();
bool getButton1();
bool getButton2();
bool getButton3();
unsigned char getButton();
unsigned char getButtonDiff();
void EXTI2_handler() __interrupt (5);

#endif
