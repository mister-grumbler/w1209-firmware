#ifndef PARAMS_H
#define PARAMS_H

/* Definition for parameters */
#define PARAM_RELAY_MODE                0
#define PARAM_RELAY_HYSTERESIS          1
#define PARAM_MAX_TEMPERATURE           2
#define PARAM_MIN_TEMPERATURE           3
#define PARAM_TEMPERATURE_CORRECTION    4
#define PARAM_RELAY_DELAY               5
#define PARAM_OVERHEAT_INDICATION       6
#define PARAM_THRESHOLD                 9

void initParamsEEPROM();
int getParamById (unsigned char);
void setParamById (unsigned char, int);
int getParam();
void setParam (int);
void incParam();
void decParam();
unsigned char getParamId();
void setParamId (unsigned char);
void incParamId();
void decParamId();
void paramToString (unsigned char, unsigned char*);
void storeParams();

#endif
