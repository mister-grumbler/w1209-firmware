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
static int paramCache[10];
const int paramMin[] = {0,1,-45,-50,-70,0,0,0,0,-500};
const int paramMax[] = {1,150,110,105,70,10,1,0,0,1100};
const int paramDefault[] = {0,20,110,-50,0,0,0,0,00,20};

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
int getParamById(unsigned char id) {
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
void setParamById(unsigned char id, int val) {
    if (id < 10) {
        paramCache[id] = val;
    }
}

/**
 * @brief 
 * @return 
 */
int getParam() {
    return paramCache[paramId];
}

/**
 * @brief 
 * @param val
 */
void setParam(int val) {
    paramCache[paramId] = val;
}

/**
 * @brief Incrementing the value of the currently selected parameter.
 */
void incParam() {
    if (paramId == PARAM_RELAY_MODE || paramId == PARAM_OVERHEAT_INDICATION) {
        paramCache[paramId] = ~paramCache[paramId] & 0x0001;
    } else if (paramCache[paramId] < paramMax[paramId]) {
        paramCache[paramId]++;
    }
}

/**
 * @brief Decrementing the value of the currently selected parameter.
 */
void decParam() {
    if (paramId == PARAM_RELAY_MODE || paramId == PARAM_OVERHEAT_INDICATION) {
        paramCache[paramId] = ~paramCache[paramId] & 0x0001;
    } else if (paramCache[paramId] > paramMin[paramId]) {
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
 * @brief Converts the current value of the selected parameter to a string.
 * @param id
 *  The identifier of the parameter to be processed.
 * @param strBuff
 *  A pointer to a string buffer where the result should be placed.
 */
void paramToString(unsigned char id, unsigned char* strBuff) {
    switch(id) {
        case PARAM_RELAY_MODE:
            if (paramCache[id]) {
                ((unsigned char*) strBuff)[0] = 'H';
            } else {
                ((unsigned char*) strBuff)[0] = 'C';
            }
            ((unsigned char*) strBuff)[1] = 0;
            break;
        case PARAM_RELAY_HYSTERESIS:
            itofpa(paramCache[id], strBuff, 0);
            break;
        case PARAM_MAX_TEMPERATURE:
            itofpa(paramCache[id], strBuff, 6);
            break;
        case PARAM_MIN_TEMPERATURE:
            itofpa(paramCache[id], strBuff, 6);
            break;
        case PARAM_TEMPERATURE_CORRECTION:
            itofpa(paramCache[id], strBuff, 0);
            break;
        case PARAM_RELAY_DELAY:
            itofpa(paramCache[id], strBuff, 6);
            break;
        case PARAM_OVERHEAT_INDICATION:
            ((unsigned char*) strBuff)[0] = 'O';
            if (paramCache[id]) {
                ((unsigned char*) strBuff)[1] = 'N';
                ((unsigned char*) strBuff)[2] = ' ';
            } else {
                ((unsigned char*) strBuff)[1] = 'F';
                ((unsigned char*) strBuff)[2] = 'F';
            }
            ((unsigned char*) strBuff)[3] = 0;
            break;
        case PARAM_THRESHOLD:
            itofpa(paramCache[id], strBuff, 0);
            break;
        default: // Display "OFF" to all unknown ID
            ((unsigned char*) strBuff)[0] = 'O';
            ((unsigned char*) strBuff)[1] = 'F';
            ((unsigned char*) strBuff)[2] = 'F';
            ((unsigned char*) strBuff)[3] = 0;
    }
}

/**
 * @brief 
 */
void storeParams() {
    unsigned char i;

    //  Check if the EEPROM is write-protected.  If it is then unlock the EEPROM.
    if ((FLASH_IAPSR & 0x08) == 0) {
        FLASH_DUKR = 0xAE;
        FLASH_DUKR = 0x56;
    }

    //  Write to the EEPROM parameters which value is changed.
    for (i = 0; i < 10; i++) {
        if ((char) paramCache[i] != (*(char*) (EEPROM_BASE_ADDR + i))) {
            *(char*) (EEPROM_BASE_ADDR + EEPROM_PARAMS_OFFSET + i) = (char)paramCache[i];
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
