#ifndef ADC_H
#define ADC_H

void initADC();
void startADC();
unsigned int getAdcResult();
unsigned int getAdcAveraged();
int getTemperature();
void ADC1_EOC_handler() __interrupt (22);

#endif