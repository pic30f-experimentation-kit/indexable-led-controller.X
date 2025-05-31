#include "peripheral-pwm.h"

#include "leds.h"

#include <xc.h>

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; //Clear interrupt flag    
    OC2RS = ledsGetPWMDutyCycle(); //Store into DC buffer register
}

void initializePWM() {    
    //we will use OC2
    TRISBbits.TRISB9 = 0; // OC2 is output
    ADPCFGbits.PCFG9 = 1; // AN9/RB9 is configured as digital
    
    //110 Without Fault mode. 111 With Fault mode
    OC2CONbits.OCM = 6;
    
    //We will use Timer2
    OC2CONbits.OCTSEL = 0;
    
    //Set PWM period.
    T2CONbits.TCKPS = 0; //Pre scaler 1:1
    PR2 = PWM_PERIOD; //Period register
    OC2RS = PWM_DC_FOR_RESET; //DC buffer register
    OC2R = PWM_DC_FOR_RESET;  //Read Only DC register
    
    //Enable interrupts -> interrupt when timer for period is reached
    IPC0bits.T1IP = 2; //priority 2 for time interrupts
    IFS0bits.T2IF = 0; //clear interrupt flag for timer 2
    IEC0bits.T2IE = 1; //Enable interrupts for timer 2
    T2CONbits.TON = 1; //Start Timer 2           
}
