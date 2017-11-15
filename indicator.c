/**
 * Control functions for the seven-segment display (SSD).
 */

#include "ts.h"

const unsigned char Hex2CharMap[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

unsigned char activeDigitId;
unsigned char displayAC[3];
unsigned char displayD[3];

static void enableDigit(unsigned char);
static void setDigit(unsigned char, unsigned char, bool);

static bool displayOff;
static bool testMode;

/**
 * @brief Configure appropriate bits for GPIO ports, initialize static
 *  variables and set test mode for display.
 */
void initIndicator() {
    PA_DDR |= SSD_SEG_B_BIT | SSD_SEG_F_BIT;
    PA_CR1 |= SSD_SEG_B_BIT | SSD_SEG_F_BIT;
    PB_DDR |= SSD_DIGIT_1_BIT | SSD_DIGIT_2_BIT;
    PB_CR1 |= SSD_DIGIT_1_BIT | SSD_DIGIT_2_BIT;
    PC_DDR |= SSD_SEG_C_BIT | SSD_SEG_G_BIT;
    PC_CR1 |= SSD_SEG_C_BIT | SSD_SEG_G_BIT;
    PD_DDR |= SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT | SSD_SEG_P_BIT | SSD_DIGIT_3_BIT;
    PD_CR1 |= SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT | SSD_SEG_P_BIT | SSD_DIGIT_3_BIT;
    displayOff= false;
    activeDigitId = 0;
    setDisplayTestMode(true);
}

/**
 * @brief This function is being called during timer's interrupt
 *  request so keep it extremely small and fast. During this call
 *  the data from display's buffer being used to drive appropriate
 *  GPIO pins of microcontroller.
 */
void refreshDisplay() {
    if (displayOff) {
        enableDigit(3);
        return;
    }
    SSD_SEG_BF_PORT &= ~SSD_BF_PORT_MASK;
    SSD_SEG_BF_PORT |= displayAC[activeDigitId] & SSD_BF_PORT_MASK;
    SSD_SEG_CG_PORT &= ~SSD_CG_PORT_MASK;
    SSD_SEG_CG_PORT |= displayAC[activeDigitId] & SSD_CG_PORT_MASK;
    SSD_SEG_AEDP_PORT &= ~SSD_AEDP_PORT_MASK;
    SSD_SEG_AEDP_PORT |= displayD[activeDigitId];
    enableDigit(activeDigitId);
    if (activeDigitId > 1) {
        activeDigitId = 0;
    } else {
        activeDigitId++;
    }
}

/**
 * @brief Enables/disables a test mode of SSDisplay. While in this mode
 *  the test message will be displayed and any attempts to update
 *  display's buffer will be ignored.
 * @param value to be set: true - enable test mode, false - disable test mode.
 */
void setDisplayTestMode(bool val) {
    const unsigned char* tstMsg = "8.8.8.";

    if (!testMode && val) {
        setDisplayStr(tstMsg);
    }
    testMode = val;
}

/**
 * @brief Enable/disable display.
 * @param value to be set: true - display off, false - display on.
 */
void setDisplayOff(bool val) {
    displayOff = val;
}

/**
 * @brief 
 * @param id
 * @param val
 */
void setDisplayDot(unsigned char id, bool val) {
    if (val) {
        displayD[id] |= SSD_SEG_P_BIT;
    } else {
        displayD[id] &= ~SSD_SEG_P_BIT;
    }
}

/**
 * @brief Sets symbols of given null-terminated string into display's buffer.
 * @param val
 */
void setDisplayStr(const unsigned char* val){
    unsigned char i, d;
    for (i = 0, d = 3; *val+i != '\0' && d != 0; i++, d--) {
        if (*(val+i+1) == '.') {
            setDigit(d-1, *(val+i), true);
            i++;
        } else {
            setDigit(d-1, *(val+i), false);
        }
    }
}

/**
 * @brief 
 * @param val
 */
void setDisplayUCharHex(unsigned char val){
    setDigit(0, Hex2CharMap[val & 0x0F], false);
    setDigit(1, Hex2CharMap[(val & 0xF0) >> 4], false);
}

/**
 * @brief 
 * @param val
 */
void setDisplayUIntHex(unsigned int val) {
    setDigit(0, Hex2CharMap[val & 0x000F], false);
    setDigit(1, Hex2CharMap[(val & 0x00F0) >> 4], false);
    setDigit(2, Hex2CharMap[(val & 0x0F00) >> 8], false);
}

/**
 * @brief 
 * @param val
 */
void setDisplayUInt(unsigned int val) {
    unsigned int output = 0;
    signed char a;

    for (a = 13; a >= 0; a--) {
        if ((output & 0xF) >= 5)
            output += 3;
        if (((output & 0xF0) >> 4) >= 5)
            output += (3 << 4);
        if (((output & 0xF00) >> 8) >= 5)
            output += (3 << 8);
        output = (output << 1) | ((val >> a) & 1);
    }
    setDisplayUIntBCD(output);
}

/**
 * @brief 
 * @param val
 */
void setDisplayUChar(unsigned char val) {
    unsigned char tmp;

    if (val >= 100) {
        tmp = val / 100;
        if (tmp > 0) setDigit(2, Hex2CharMap[tmp], false);
        val = val - (tmp * 100);
    } else {
        setDigit(2, Hex2CharMap[0], false);
    }

    if (val >= 10) {
        tmp = val / 10;
        if (tmp > 0) setDigit(1, Hex2CharMap[tmp], false);
        val = val - (tmp * 10);
    } else {
        setDigit(1, Hex2CharMap[0], false);
    }

    setDigit(0, Hex2CharMap[val], false);
}

/**
 * @brief 
 * @param val
 */
void setDisplayUCharBCD(unsigned char val) {
    setDigit(2, Hex2CharMap[0], false);
    setDigit(1, Hex2CharMap[(val & 0xF0) >> 4], false);
    setDigit(0, Hex2CharMap[val & 0xF], false);
}

/**
 * @brief 
 * @param val
 */
void setDisplayUIntBCD(unsigned int val) {
    setDigit(2, Hex2CharMap[(val & 0xF00) >> 8], false);
    setDigit(1, Hex2CharMap[(val & 0xF0) >> 4], false);
    setDigit(0, Hex2CharMap[val & 0xF], false);
}


/**
 * @brief 
 * Enable the digit with given ID on SSD and rest of digits are disabled.
 * 
 * @param id
 * The ID = 0 corresponds to the right most digit on the display.
 * Accepted values are: 0, 1, 2, any other value will disable display.
 */
static void enableDigit(unsigned char id) {
    switch (id) {
        case 0:
            SSD_DIGIT_12_PORT &= ~SSD_DIGIT_1_BIT;
            SSD_DIGIT_12_PORT |= SSD_DIGIT_2_BIT;
            SSD_DIGIT_3_PORT |= SSD_DIGIT_3_BIT;
            break;
        case 1:
            SSD_DIGIT_12_PORT &= ~SSD_DIGIT_2_BIT;
            SSD_DIGIT_12_PORT |= SSD_DIGIT_1_BIT;
            SSD_DIGIT_3_PORT |= SSD_DIGIT_3_BIT;
            break;
        case 2:
            SSD_DIGIT_3_PORT &= ~SSD_DIGIT_3_BIT;
            SSD_DIGIT_12_PORT |= SSD_DIGIT_1_BIT | SSD_DIGIT_2_BIT;
            break;
        default:
            SSD_DIGIT_12_PORT |= SSD_DIGIT_1_BIT | SSD_DIGIT_2_BIT;
            SSD_DIGIT_3_PORT |= SSD_DIGIT_3_BIT;
            break;
    }
}

/**
 * @brief Sets bits within display's buffer appropriate to given value.
 *  So this symbol will be shown on indicator during refreshDisplay() call.
 *  When test mode is enabled the display's buffer will not be updated.
 * 
 * The list of segments as they located on display:
 *  _2_       _1_       _0_
 *  <A>       <A>       <A>
 * F   B     F   B     F   B
 *  <G>       <G>       <G>
 * E   C     E   C     E   C
 *  <D> (P)   <D> (P)   <D> (P)
 * 
 * @param id
 *  Identifier of character's position on display.
 *  Accepted values are: 0, 1, 2.
 * @param val
 *  Character to be represented on SSD at position being designated by id.
 *  Due to limited capabilities of SSD some characters are shown in a very
 *  schematic manner.
 *  Accepted values are: ANY.
 *  But at the moment actual characters are shown only for 0-9, A-Z, ' ', '-'.
 *  For the rest of values the '_' symbol is shown because no one knows which
 *  symbol would be added or removed tomorrow.
 * @param dot
 *  Enable dot (decimal point) for the character.
 *  Accepted values true/false.
 *  
 */
static void setDigit(unsigned char id, unsigned char val, bool dot) {

    if (id > 2) return;
    if (testMode) return;

    switch (val) {
        case '-':
            displayAC[id] = SSD_SEG_G_BIT;
            displayD[id] = 0;
            break;
        case ' ':
            displayAC[id] = 0;
            displayD[id] = 0;
            break;
        case '0':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_F_BIT | SSD_SEG_C_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case '1':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT;
            displayD[id] = 0;
            break;
        case '2':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case '3':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT;
            break;
        case '4':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = 0;
            break;
        case '5':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT;
            break;
        case '6':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case '7':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT;
            displayD[id] = SSD_SEG_A_BIT;
            break;
        case '8':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case '9':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT;
            break;
        case 'A':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
            break;
        case 'B':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'C':
            displayAC[id] = SSD_SEG_F_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'D':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'E':
            displayAC[id] = SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'F':
            displayAC[id] = SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
            break;
        case 'G':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_F_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'H':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_E_BIT;
            break;
        case 'I':
            displayAC[id] = SSD_SEG_F_BIT;
            displayD[id] = SSD_SEG_E_BIT;
            break;
        case 'J':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT;
            displayD[id] = SSD_SEG_D_BIT;
            break;
        case 'K':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
            break;
        case 'L':
            displayAC[id] = SSD_SEG_F_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'M':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
            break;
        case 'N':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_E_BIT;
            break;
        case 'O':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'P':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
            break;
        case 'Q':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_A_BIT;
            break;
        case 'R':
            displayAC[id] = SSD_SEG_F_BIT;
            displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
            break;
        case 'S':
            displayAC[id] = SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT;
            break;
        case 'T':
            displayAC[id] = SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'U':
            displayAC[id] = SSD_SEG_C_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'V':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        case 'W':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT;
            break;
        case 'X':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_E_BIT;
            break;
        case 'Y':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT;
            break;
        case 'Z':
            displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_G_BIT;
            displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
            break;
        default:
            displayAC[id] = 0;
            displayD[id] = SSD_SEG_D_BIT;
    }

    if (dot) {
        displayD[id] |= SSD_SEG_P_BIT;
    } else {
        displayD[id] &= ~SSD_SEG_P_BIT;
    }

    return;
}