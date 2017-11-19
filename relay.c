#include "ts.h"

static unsigned int timer;
static bool mode;

/**
 * @brief Configure appropriate bits for GPIO port A, reset local timer
 *  and reset mode.
 */
void initRelay() {
    PA_DDR |= RELAY_BIT;
    PA_CR1 |= RELAY_BIT;
    timer = 0;
    mode = false;
}

/**
 * @brief Sets state of the relay.
 * @param on - true, off - false
 */
void setRelay(bool on) {
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
void refreshRelay() {
    if (mode) { // Relay mode is enabled
        if (getTemperature() < (getParamById(PARAM_THRESHOLD)
            - (getParamById(PARAM_RELAY_HYSTERESIS) >> 3))) {
            timer++;
            if ((getParamById(PARAM_RELAY_DELAY) << RELAY_TIMER_MULTIPLIER) < timer) {
                mode = false;
                setRelay(getParamById(PARAM_RELAY_MODE));
            } else {
                setRelay(!getParamById(PARAM_RELAY_MODE));
            }
        } else {
            timer = 0;
            setRelay(!getParamById(PARAM_RELAY_MODE));
        }
    } else { // Relay mode is disabled
        if (getTemperature() > (getParamById(PARAM_THRESHOLD)
            + (getParamById(PARAM_RELAY_HYSTERESIS) >> 3))) {
            timer++;
            if ((getParamById(PARAM_RELAY_DELAY) << RELAY_TIMER_MULTIPLIER) < timer) {
                mode = true;
                setRelay(!getParamById(PARAM_RELAY_MODE));
            } else {
                setRelay(getParamById(PARAM_RELAY_MODE));
            }
        } else {
            timer = 0;
            setRelay(getParamById(PARAM_RELAY_MODE));
        }
    }
}