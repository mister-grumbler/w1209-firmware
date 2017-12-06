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

#ifndef PARAMS_H
#define PARAMS_H

/* Definition for parameter identifiers */
#define PARAM_RELAY_MODE                0
#define PARAM_RELAY_HYSTERESIS          1
#define PARAM_MAX_TEMPERATURE           2
#define PARAM_MIN_TEMPERATURE           3
#define PARAM_TEMPERATURE_CORRECTION    4
#define PARAM_RELAY_DELAY               5
#define PARAM_OVERHEAT_INDICATION       6
#define PARAM_THRESHOLD                 9

int getParam();
void incParam();
void decParam();
void incParamId();
void decParamId();
void storeParams();
void initParamsEEPROM();
unsigned char getParamId();
int getParamById (unsigned char);
void setParam (int);
void setParamId (unsigned char);
void setParamById (unsigned char, int);
void paramToString (unsigned char, unsigned char*);
void itofpa (int, unsigned char*, unsigned char);

#endif
