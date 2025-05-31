#ifndef PERIPHERAL_PWM_H
#define	PERIPHERAL_PWM_H

// At selected pre-scaler and Fosc...
#define PWM_PERIOD       0     // TODO
#define PWM_DC_FOR_1     0     // TODO
#define PWM_DC_FOR_0     0     // TODO
#define PWM_DC_FOR_RESET 0     // During the reset, no DC at all.

/**
 * Initializes PWM peripheral.
 */
void initializePWM();  

#endif /* PERIPHERAL_PWM_H */

