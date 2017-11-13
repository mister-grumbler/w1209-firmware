/*
 * Control functions for analog-to-digital converter (ADC).
 */

#include "ts.h"

static unsigned int result;
static unsigned long averaged;

/*
 * Initialize ADC's configuration registers 
 */
void initADC() {
    ADC_CR1 |= 0x70;    // Prescaler f/18 (SPSEL)
    ADC_CSR |= 0x06;    // select AIN6
    ADC_CSR |= 0x20;    // Interrupt enable (EOCIE)
    ADC_CR1 |= 0x01;    // Power up ADC
    result = 0;
    averaged = 0;
}

void startADC() {
    ADC_CR1 |= 0x01;
}

unsigned int getAdcResult() {
    return result;
}

unsigned int getAdcAveraged() {
    return (unsigned int)(averaged >> ADC_AVERAGING_BITS);
}

/**
 * This function is interrupt request handler
 * so keep it extremely small and fast.
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
