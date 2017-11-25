/**
 * Control functions for analog-to-digital converter (ADC).
 */

#include "ts.h"

static unsigned int result;
static unsigned long averaged;

// The lookup table contains raw ADC values for every degree of Celsius
// from -52C to 112C.
const unsigned int rawAdc[] = {
    974, 971, 967, 964, 960, 956, 953, 948,
    944, 940, 935, 930, 925, 920, 914, 909,
    903, 897, 891, 884, 877, 871, 864, 856,
    849, 841, 833, 825, 817, 809, 800, 791,
    782, 773, 764, 754, 745, 735, 725, 715,
    705, 695, 685, 675, 664, 654, 644, 633,
    623, 612, 601, 591, 580, 570, 559, 549,
    538, 528, 518, 507, 497, 487, 477, 467,
    457, 448, 438, 429, 419, 410, 401, 392,
    383, 375, 366, 358, 349, 341, 333, 326,
    318, 310, 303, 296, 289, 282, 275, 269,
    262, 256, 250, 244, 238, 232, 226, 221,
    215, 210, 205, 200, 195, 191, 186, 181,
    177, 173, 169, 165, 161, 157, 153, 149,
    146, 142, 139, 136, 132, 129, 126, 123,
    120, 117, 115, 112, 109, 107, 104, 102,
    100, 97, 95, 93, 91, 89, 87, 85,
    83, 81, 79, 78, 76, 74, 73, 71,
    69, 68, 67, 65, 64, 62, 61, 60,
    58, 57, 56, 55, 54, 53, 52, 51,
    49, 48, 47, 47, 46
};

#define ADC_RAW_TABLE_SIZE          sizeof rawAdc / sizeof rawAdc[0]
// Base temperature in tenth of degrees of Celsius.
#define ADC_RAW_TABLE_BASE_TEMP     -520

/**
 * @brief Initialize ADC's configuration registers.
 */
void initADC() {
    ADC_CR1 |= 0x70;    // Prescaler f/18 (SPSEL)
    ADC_CSR |= 0x06;    // select AIN6
    ADC_CSR |= 0x20;    // Interrupt enable (EOCIE)
    ADC_CR1 |= 0x01;    // Power up ADC
    result = 0;
    averaged = 0;
}

/**
 * @brief Sets bit in ADC control register to start data convertion.
 */
void startADC() {
    ADC_CR1 |= 0x01;
}

/**
 * @brief Gets raw result of last data conversion.
 * @return raw result.
 */
unsigned int getAdcResult() {
    return result;
}

/**
 * @brief Gets averaged over 2^ADC_AVERAGING_BITS times result of data
 *  convertion.
 * @return averaged result.
 */
unsigned int getAdcAveraged() {
    return (unsigned int)(averaged >> ADC_AVERAGING_BITS);
}

/**
 * @brief Calculation of real temperature using averaged result of
 *  AnalogToDigital conversion and the lookup table.
 * @return temperature in tenth of degrees of Celsius.
 */
int getTemperature() {
    unsigned int val = averaged >> ADC_AVERAGING_BITS;
    unsigned char rightBound = ADC_RAW_TABLE_SIZE;
    unsigned char leftBound = 0;

    // search
    while ((rightBound - leftBound) > 1) {
        unsigned char midId = (leftBound + rightBound) >> 1;
        if (val > rawAdc[midId]) {
            rightBound = midId;
        } else {
            leftBound = midId;
        }
    }
    // reusing the "val" for storing an intermediate result
    if (val >= rawAdc[leftBound]) {
        val = leftBound * 10;
    } else {
        val = (rightBound * 10) - ((val - rawAdc[rightBound]) * 10)
                / (rawAdc[leftBound] - rawAdc[rightBound]);
    }
    // Final calculation and correction
    return ADC_RAW_TABLE_BASE_TEMP + val + getParamById(PARAM_TEMPERATURE_CORRECTION);
}

/**
 * @brief This function is ADC's interrupt request handler
 *  so keep it extremely small and fast.
 */
void ADC1_EOC_handler() __interrupt(22) {
    result = ADC_DRH << 2;
    result |= ADC_DRL;
    ADC_CSR &= ~0x80;   // reset EOC
    // Averaging result
    if(averaged == 0) {
        averaged = result << ADC_AVERAGING_BITS;
    } else {
        averaged += result - (averaged >> ADC_AVERAGING_BITS);
    }
}
