/**
 * Control functions for EEPROM storage of persistent application parameters.
 * 
 * The list of aplication parameters with default values:
 * Name |Def| Description
 * -----+---+---------------------------------------------
 * P0 - | C | Cooling/Heating
 *            (relay ON when temperature is over(C)/below(H) threshold value)
 * P1 - | 2 | 0.1 ... 15.0 - Hysteresis
 * P2 - |110| 110 ... -45 - Maximum allowed temperature value
 * P3 - |-50| -50 ... 105 Minimum allowed temperature value
 * P4 - | 0 | 7.0 ... -7.0 Correction of temperature value
 * P5 - | 0 | 0 ... 10 Relay switching delay in minutes
 * P6 - |Off| On/Off Indication of overheating
 * TH - | 20| Threshold value
 */

#include "ts.h"

static unsigned char paramId;
static signed char paramCache[10];
const signed char paramMin[] = {0,1,-45,-50,-70,0,0,0,-50,0};
const signed char paramMax[] = {1,126,110,105,70,10,1,0,110,0};
const signed char paramDefault[] = {0,20,110,-50,0,0,0,0,20,0};

void initParamsEEPROM() {
    for (paramId = 0; paramId < 10; paramId++) {
        paramCache[paramId] = paramDefault[paramId];
    }
    paramId = 0;
}

signed char getParam(unsigned char id) {
    if (id < 10) {
        return paramCache[id];
    }
    return -1;
}

void setParam(unsigned char id, signed char val) {
    if (id < 10) {
        paramCache[id] = val;
    }
}

void incParam() {
    if (paramId < 10 && paramCache[paramId] < paramMax[paramId]) {
        paramCache[paramId]++;
    }
}

void decParam() {
    if (paramId < 10 && paramCache[paramId] > paramMin[paramId]) {
        paramCache[paramId]--;
    }
}

unsigned char getParamId() {
    return paramId;
}

void setParamId(unsigned char val) {
    if (val < 10) paramId = val;
}

void incParamId() {
    if (paramId < 10) paramId++;
}

void decParamId() {
    if (paramId > 0) paramId--;
}

void storeParams() {
    char i;

    //  Check if the EEPROM is write-protected.  If it is then unlock the EEPROM.
    if ((FLASH_IAPSR & 0x08) == 0) {
        FLASH_DUKR = 0xAE;
        FLASH_DUKR = 0x56;
    }

    //  Write to the EEPROM parameters which value is changed.
    for (i = 0; i < 10; i++) {
        if ((unsigned char) paramCache[i] != (*(unsigned char*) (EEPROM_BASE_ADDR + i))) {
            *(unsigned char*) (EEPROM_BASE_ADDR + EEPROM_PARAMS_OFFSET + i) = (unsigned char)paramCache[i];
        }
    }

    //  Now write protect the EEPROM.
    FLASH_IAPSR &= ~0x08;
}

static void writeEEPROM(unsigned char val, unsigned char offset) {
    //  Check if the EEPROM is write-protected.  If it is then unlock the EEPROM.
    if ((FLASH_IAPSR & 0x08) == 0) {
        FLASH_DUKR = 0xAE;
        FLASH_DUKR = 0x56;
    }

    //  Write the data to the EEPROM.
    (*(unsigned char*) (EEPROM_BASE_ADDR + offset)) = val;

    //  Now write protect the EEPROM.
    FLASH_IAPSR &= ~0x08;
}
