/**
 * Control functions for the seven-segment display (SSD).
 */

#include "ts.h"

/* Definitions for indicator */
// Port A controls segments: B, F
// 0000 0110
#define SSD_SEG_BF_PORT     PA_ODR
#define SSD_BF_PORT_MASK    0b00000110
// Port C controls segments: C, G
// 1100 0000
#define SSD_SEG_CG_PORT     PC_ODR
#define SSD_CG_PORT_MASK    0b11000000
// Port D controls segments: A, E, D, P
// 0010 1110
#define SSD_SEG_AEDP_PORT   PD_ODR
#define SSD_AEDP_PORT_MASK  0b00101110

// PD.5
#define SSD_SEG_A_BIT       0x20
// PA.2
#define SSD_SEG_B_BIT       0x04
// PC.7
#define SSD_SEG_C_BIT       0x80
// PD.3
#define SSD_SEG_D_BIT       0x08
// PD.1
#define SSD_SEG_E_BIT       0x02
// PA.1
#define SSD_SEG_F_BIT       0x02
// PC.6
#define SSD_SEG_G_BIT       0x40
// PD.2
#define SSD_SEG_P_BIT       0x04

// Port B controls digits: 1, 2
#define SSD_DIGIT_12_PORT   PB_ODR
// Port D controls digit: 3
#define SSD_DIGIT_3_PORT    PD_ODR

// PB.4
#define SSD_DIGIT_1_BIT     0x10
// PB.5
#define SSD_DIGIT_2_BIT     0x20
// PD.4
#define SSD_DIGIT_3_BIT     0x10

#define SSD_BUFFER_SIZE     6

const unsigned char Hex2CharMap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
                                     'B', 'C', 'D', 'E', 'F'
                                    };

static unsigned char activeDigitId;
static unsigned char displayAC[3];
static unsigned char displayD[3];
static unsigned char* stringBuffer[SSD_BUFFER_SIZE];

static void enableDigit (unsigned char);
static void setDigit (unsigned char, unsigned char, bool);

static bool displayOff;
static bool testMode;

/**
 * @brief Configure appropriate bits for GPIO ports, initialize static
 *  variables and set test mode for display.
 */
void initIndicator()
{
    unsigned char i;

    PA_DDR |= SSD_SEG_B_BIT | SSD_SEG_F_BIT;
    PA_CR1 |= SSD_SEG_B_BIT | SSD_SEG_F_BIT;
    PB_DDR |= SSD_DIGIT_1_BIT | SSD_DIGIT_2_BIT;
    PB_CR1 |= SSD_DIGIT_1_BIT | SSD_DIGIT_2_BIT;
    PC_DDR |= SSD_SEG_C_BIT | SSD_SEG_G_BIT;
    PC_CR1 |= SSD_SEG_C_BIT | SSD_SEG_G_BIT;
    PD_DDR |= SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT | SSD_SEG_P_BIT | SSD_DIGIT_3_BIT;
    PD_CR1 |= SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT | SSD_SEG_P_BIT | SSD_DIGIT_3_BIT;
    displayOff = false;
    activeDigitId = 0;
    setDisplayTestMode (true);

    for (i = 0; i > SSD_BUFFER_SIZE; i++) {
        stringBuffer[i] = 0;
    }
}

/**
 * @brief This function is being called during timer's interrupt
 *  request so keep it extremely small and fast. During this call
 *  the data from display's buffer being used to drive appropriate
 *  GPIO pins of microcontroller.
 */
void refreshDisplay()
{
    enableDigit (3);

    if (displayOff) {
        return;
    }

    SSD_SEG_BF_PORT &= ~SSD_BF_PORT_MASK;
    SSD_SEG_BF_PORT |= displayAC[activeDigitId] & SSD_BF_PORT_MASK;
    SSD_SEG_CG_PORT &= ~SSD_CG_PORT_MASK;
    SSD_SEG_CG_PORT |= displayAC[activeDigitId] & SSD_CG_PORT_MASK;
    SSD_SEG_AEDP_PORT &= ~SSD_AEDP_PORT_MASK;
    SSD_SEG_AEDP_PORT |= displayD[activeDigitId];
    enableDigit (activeDigitId);

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
void setDisplayTestMode (bool val)
{
    const unsigned char* tstMsg = "888";

    if (!testMode && val) {
        setDisplayStr (tstMsg);
    }

    testMode = val;
}

/**
 * @brief Enable/disable display.
 * @param value to be set: true - display off, false - display on.
 */
void setDisplayOff (bool val)
{
    displayOff = val;
}

/**
 * @brief
 * @param id
 * @param val
 */
void setDisplayDot (unsigned char id, bool val)
{
    if (val) {
        displayD[id] |= SSD_SEG_P_BIT;
    } else {
        displayD[id] &= ~SSD_SEG_P_BIT;
    }
}

/**
 * @brief Construction of a string representation of the given value.
 *  To emulate a floating-point value, a decimal point can be inserted
 *  before a certain digit.
 *  When the decimal point is not needed, set pointPosition to 6 or more.
 * @param val
 *  the value to be processed.
 * @param str
 *  pointer to buffer for constructed string.
 * @param pointPosition
 *  put the decimal point in front of specified digit.
 */
void itofpa (int val, unsigned char* str, unsigned char pointPosition)
{
    unsigned char i, l, buffer[] = {0, 0, 0, 0, 0, 0};
    bool minus = false;

    // No calculation is required for zero value
    if (val == 0) {
        ( (unsigned char*) str) [0] = '0';
        ( (unsigned char*) str) [1] = 0;
        return;
    }

    // Correction for processing of negative value
    if (val < 0) {
        minus = true;
        val = -val;
    }

    // Forming the reverse string
    for (i = 0; val != 0; i++) {
        buffer[i] = '0' + (val % 10);

        if (i == pointPosition) {
            i++;
            buffer[i] = '.';
        }

        val /= 10;
    }

    // Add leading '0' in case of ".x" result
    if (buffer[i - 1] == '.') {
        buffer[i] = '0';
        i++;
    }

    // Add '-' sign for negative values
    if (minus) {
        buffer[i] = '-';
        i++;
    }

    // Reversing to get the result string
    for (l = i; i > 0; i--) {
        ( (unsigned char*) str) [l - i] = buffer[i - 1];
    }

    // Put null at the end of string
    ( (unsigned char*) str) [l] = 0;
}

void setDisplayInt (int val)
{
    itofpa (val, (unsigned char *) stringBuffer, 0);
    setDisplayStr ( (unsigned char*) stringBuffer);
}

/**
 * @brief Sets symbols of given null-terminated string into display's buffer.
 * @param val
 */
void setDisplayStr (const unsigned char* val)
{
    unsigned char i, d;

    // get number of display digit(s) required to show given string.
    for (i = 0, d = 0; * (val + i) != 0; i++, d++) {
        if (* (val + i) == '.' && i > 0 && * (val + i - 1) != '.') d--;
    }

    // at this point d = required digits
    // but SSD have 3 digits only. So rest is doesn't matters.
    if (d > 3) {
        d = 3;
    }

    // disable the digit if it is not needed.
    for (i = 3 - d; i > 0; i--) {
        setDigit (3 - i, ' ', false);
    }

    // set values for digits.
    for (i = 0; d != 0 && *val + i != 0; i++, d--) {
        if (* (val + i + 1) == '.') {
            setDigit (d - 1, * (val + i), true);
            i++;
        } else {
            setDigit (d - 1, * (val + i), false);
        }
    }
}

/**
 * @brief
 * @param val
 */
void setDisplayUCharHex (unsigned char val)
{
    setDigit (0, Hex2CharMap[val & 0x0F], false);
    setDigit (1, Hex2CharMap[ (val & 0xF0) >> 4], false);
}

/**
 * @brief
 * @param val
 */
void setDisplayUIntHex (unsigned int val)
{
    setDigit (0, Hex2CharMap[val & 0x000F], false);
    setDigit (1, Hex2CharMap[ (val & 0x00F0) >> 4], false);
    setDigit (2, Hex2CharMap[ (val & 0x0F00) >> 8], false);
}

/**
 * @brief
 * @param val
 */
void setDisplayUInt (unsigned int val)
{
    unsigned int output = 0;
    signed char a;

    for (a = 13; a >= 0; a--) {
        if ( (output & 0xF) >= 5) {
            output += 3;
        }

        if ( ( (output & 0xF0) >> 4) >= 5) {
            output += (3 << 4);
        }

        if ( ( (output & 0xF00) >> 8) >= 5) {
            output += (3 << 8);
        }

        output = (output << 1) | ( (val >> a) & 1);
    }

    setDisplayUIntBCD (output);
}

/**
 * @brief
 * @param val
 */
void setDisplayUChar (unsigned char val)
{
    unsigned char tmp;

    if (val >= 100) {
        tmp = val / 100;

        if (tmp > 0) {
            setDigit (2, Hex2CharMap[tmp], false);
        }

        val = val - (tmp * 100);
    } else {
        setDigit (2, Hex2CharMap[0], false);
    }

    if (val >= 10) {
        tmp = val / 10;

        if (tmp > 0) {
            setDigit (1, Hex2CharMap[tmp], false);
        }

        val = val - (tmp * 10);
    } else {
        setDigit (1, Hex2CharMap[0], false);
    }

    setDigit (0, Hex2CharMap[val], false);
}

/**
 * @brief
 * @param val
 */
void setDisplayUCharBCD (unsigned char val)
{
    setDigit (2, Hex2CharMap[0], false);
    setDigit (1, Hex2CharMap[ (val & 0xF0) >> 4], false);
    setDigit (0, Hex2CharMap[val & 0xF], false);
}

/**
 * @brief
 * @param val
 */
void setDisplayUIntBCD (unsigned int val)
{
    setDigit (2, Hex2CharMap[ (val & 0xF00) >> 8], false);
    setDigit (1, Hex2CharMap[ (val & 0xF0) >> 4], false);
    setDigit (0, Hex2CharMap[val & 0xF], false);
}


/**
 * @brief
 * Enable the digit with given ID on SSD and rest of digits are disabled.
 *
 * @param id
 * The ID = 0 corresponds to the right most digit on the display.
 * Accepted values are: 0, 1, 2, any other value will disable display.
 */
static void enableDigit (unsigned char id)
{
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
static void setDigit (unsigned char id, unsigned char val, bool dot)
{

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

    case 'H':
        displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_C_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
        displayD[id] = SSD_SEG_E_BIT;
        break;

    case 'L':
        displayAC[id] = SSD_SEG_F_BIT;
        displayD[id] = SSD_SEG_D_BIT | SSD_SEG_E_BIT;
        break;

    case 'N':
        displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_F_BIT | SSD_SEG_C_BIT;
        displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
        break;

    case 'O':
        displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_F_BIT | SSD_SEG_C_BIT;
        displayD[id] = SSD_SEG_A_BIT | SSD_SEG_D_BIT | SSD_SEG_E_BIT;
        break;

    case 'P':
        displayAC[id] = SSD_SEG_B_BIT | SSD_SEG_F_BIT | SSD_SEG_G_BIT;
        displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
        break;

    case 'R':
        displayAC[id] = SSD_SEG_F_BIT;
        displayD[id] = SSD_SEG_A_BIT | SSD_SEG_E_BIT;
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
