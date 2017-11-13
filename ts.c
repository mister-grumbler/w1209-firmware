#include "ts.h"

extern unsigned char display[3];
//const unsigned char* paramMsg = " P0";
const unsigned char* errMsg = "ERR\0";
unsigned char paramMsg[] = {' ','P','0',0};

void gpioInit(void) {
    // Configure system clock
//    CLK_DIVR = 0x00;    // Set the frequency to 16 MHz
//    CLK_PCKENR1 = 0xFF; // Enable peripherals

    // Configure pins

    // relay PA.3
    PA_DDR = 0x0E;
    PA_CR1 = 0x0E;
    return;
}

unsigned int uInt2BCD(unsigned int val) {
    unsigned int result = 0;
    signed char a;

    for(a = 13; a >= 0; a--){
        if((result & 0xF) >= 5)
            result += 3;
        if(((result & 0xF0) >> 4) >= 5)
            result += (3 << 4);
        if(((result & 0xF00) >> 8) >= 5)
            result += (3 << 8);
        result = (result << 1) | ((val >> a) & 1);
    }
    return result;
}

int main() {
    int d,c;
    unsigned char param = 0;
    gpioInit();
    initParamsEEPROM();
    initIndicator();
    initTimer();
    initButtons();
    initADC();

    INTERRUPT_ENABLE
    // Loop
    do {
//        RELAY_PORT ^= RELAY_BIT; //toggle LED
        for(c = 0; c<4096; c++)
        {
            if (getUptimeSeconds() > 0) setDisplayTestMode(false);
            for(d = 0; d<9900; d++);
            if (getMenuDisplay() == MENU_ROOT) {
                setDisplayUInt(getAdcAveraged());
                setDisplayOff(false);
            } else if (getMenuDisplay() == MENU_SET_THRESHOLD) {
                setDisplayUCharHex(getParam(EEPROM_PARAM_THRESHOLD));
                setDisplayOff((bool)(getUptime() & 0x40));
            } else if (getMenuDisplay() == MENU_SELECT_PARAM) {
                paramMsg[2] = '0' + getParamId();
                setDisplayStr((unsigned char*)&paramMsg);
                setDisplayOff(false);
            } else if (getMenuDisplay() == MENU_CHANGE_PARAM) {
                setDisplayUCharHex(getParam(param));
                setDisplayOff(false);
            } else {
                setDisplayStr(errMsg);
                setDisplayOff((bool)(getUptime() & 0x40));
            }
//            if (displayMode == 1) {
//                setDisplayUIntBCD((uInt2BCD(getUptimeMinutes() & 0xF) << 8) | uInt2BCD(getUptimeSeconds()));
//                setDisplayDot(2, getUptime() & 0x40);
//            }
//            else if (displayMode == 2) {
//                setDisplayUIntBCD((uInt2BCD(getUptimeDays() & 0xF) << 8) | uInt2BCD(getUptimeHours()));
//                setDisplayDot(2, getUptime() & 0x40);
//            }
//            else if (displayMode == 3) {
//                setDisplayUCharHex(*(unsigned char*) (EEPROM_BASE_ADDR + param));
//                setDisplayDot(2, param & 0x1);
//            }
//            else setDisplayUInt(getAdcAveraged());
        }
        WAIT_FOR_INTERRUPT
    } while(true);

}
