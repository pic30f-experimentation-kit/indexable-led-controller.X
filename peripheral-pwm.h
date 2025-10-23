#ifndef PERIPHERAL_PWM_H
#define	PERIPHERAL_PWM_H

// At selected pre-scaler and Fosc...
#define PWM_PERIOD       147   // ... this is 5.00µs
#define PWM_DC_FOR_1     80    // ... this is 2.71µs
#define PWM_DC_FOR_0     10    // ... this is 0.35µs
#define PWM_DC_FOR_RESET 0     // During the reset, no DC at all.

#ifndef __ASSEMBLER__
/**
 * Initializes PWM peripheral.
 */
void initializePWM();  

#endif /* __ASSEMBLER__ */

#endif /* PERIPHERAL_PWM_H */

