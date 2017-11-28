#include "ts.h"

#define RELAY_PORT              PA_ODR
#define RELAY_BIT               0x08
#define RELAY_TIMER_MULTIPLIER  7

static unsigned int timer;
static bool state;

/**
 * @brief Configure appropriate bits for GPIO port A, reset local timer
 *  and reset state.
 */
void initRelay()
{
    PA_DDR |= RELAY_BIT;
    PA_CR1 |= RELAY_BIT;
    timer = 0;
    state = false;
}

/**
 * @brief Sets state of the relay.
 * @param on - true, off - false
 */
void setRelay (bool on)
{
    if (on) {
        RELAY_PORT |= RELAY_BIT;
    } else {
        RELAY_PORT &= ~RELAY_BIT;
    }

}

/**
 * @brief This function is being called during timer's interrupt
 *  request so keep it extremely small and fast.
 */
void refreshRelay()
{
    if (state) { // Relay state is enabled
        if (getTemperature() < (getParamById (PARAM_THRESHOLD)
                                - (getParamById (PARAM_RELAY_HYSTERESIS) >> 3) ) ) {
            timer++;

            if ( (getParamById (PARAM_RELAY_DELAY) << RELAY_TIMER_MULTIPLIER) < timer) {
                state = false;
                setRelay (getParamById (PARAM_RELAY_MODE) );
            } else {
                setRelay (!getParamById (PARAM_RELAY_MODE) );
            }
        } else {
            timer = 0;
            setRelay (!getParamById (PARAM_RELAY_MODE) );
        }
    } else { // Relay state is disabled
        if (getTemperature() > (getParamById (PARAM_THRESHOLD)
                                + (getParamById (PARAM_RELAY_HYSTERESIS) >> 3) ) ) {
            timer++;

            if ( (getParamById (PARAM_RELAY_DELAY) << RELAY_TIMER_MULTIPLIER) < timer) {
                state = true;
                setRelay (!getParamById (PARAM_RELAY_MODE) );
            } else {
                setRelay (getParamById (PARAM_RELAY_MODE) );
            }
        } else {
            timer = 0;
            setRelay (getParamById (PARAM_RELAY_MODE) );
        }
    }
}
