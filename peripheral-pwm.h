#ifndef PERIPHERAL_PWM_H
#define	PERIPHERAL_PWM_H

// At selected pre-scaler and Fosc...
#define PWM_PERIOD       50    // ... this is 1.71µs
#define PWM_DC_FOR_1     40    // ... this is 1.36µs
#define PWM_DC_FOR_0     10    // ... this is 0.35µs
#define PWM_DC_FOR_RESET 0     // During the reset, no DC at all.

/**
 * Initializes PWM peripheral.
 */
void initializePWM();  

#endif /* PERIPHERAL_PWM_H */

