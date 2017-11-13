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
const signed char paramMin[] = {0,1,-45,-50,-70,0,0,0,0,-50};
const signed char paramMax[] = {1,126,110,105,70,10,1,0,0,110};
const signed char paramDefault[] = {0,20,110,-50,0,0,0,0,00,20};

/**
 * @brief Check values in the EEPROM to be correct then load them into parameters' cache.
 */
void initParamsEEPROM() {
    for (paramId = 0; paramId < 10; paramId++) {
        // TODO: implement check values
        paramCache[paramId] = paramDefault[paramId];
    }
    paramId = 0;
}

/**
 * @brief 
 * @param id
 * @return 
 */
signed char getParamById(unsigned char id) {
    if (id < 10) {
        return paramCache[id];
    }
    return -1;
}

/**
 * @brief 
 * @param id
 * @param val
 */
void setParamById(unsigned char id, signed char val) {
    if (id < 10) {
        paramCache[id] = val;
    }
}

/**
 * @brief 
 * @return 
 */
signed char getParam() {
    return paramCache[paramId];
}

/**
 * @brief 
 * @param val
 */
void setParam(signed char val) {
    paramCache[paramId] = val;
}

/**
 * @brief 
 */
void incParam() {
    if (paramCache[paramId] < paramMax[paramId]) {
        paramCache[paramId]++;
    }
}

/**
 * @brief 
 */
void decParam() {
    if (paramCache[paramId] > paramMin[paramId]) {
        paramCache[paramId]--;
    }
}

/**
 * @brief 
 * @return 
 */
unsigned char getParamId() {
    return paramId;
}

/**
 * @brief 
 * @param val
 */
void setParamId(unsigned char val) {
    if (val < 10) paramId = val;
}

/**
 * @brief 
 */
void incParamId() {
    if (paramId < 9) paramId++;
    else paramId = 0;
}

/**
 * @brief 
 */
void decParamId() {
    if (paramId > 0) paramId--;
    else paramId = 9;
}

/**
 * @brief 
 */
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

/**
 * @brief 
 * @param val
 * @param offset
 */
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
