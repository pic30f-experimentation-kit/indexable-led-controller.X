.include "xc.inc"
#include "peripheral-pwm.h"
#include "leds.h"
    
    .text
    .global _ledsGetPWMDutyCycle
    
_ledsGetPWMDutyCycle:
    ; Increment and load the counter
    inc	    _ledsInternalCounter, WREG	; WREG is alias for W0.
    
    ; If counter is over all lamps and pixels...
    mov	    #NUMBER_OF_BITS, W1
    cp	    W0, W1
    bra	    GE, RESET ; ... it's reset time.
    
ACTIVE:
    ; Save back the counter:
    mov	    WREG, _ledsInternalCounter ; ... and save it back.
    
    ; Compute the current pixel:
    asr	    W0, #3, W1
    mov	    #_display, W2
    add	    W1, W2, W2
    mov.b   [W2], W1
    
    ; Compute the current bit of the current pixel
    and	    #7, W0
    sl	    W1, W0, W1
    
    ; Test whether it is 1 or 0:
    and	    #128, W1
    bra	    Z, ACTIVE_ZERO
    
ACTIVE_ONE:
    retlw   #PWM_DC_FOR_1, W0    ; Return the corresponding value

ACTIVE_ZERO:
    retlw   #PWM_DC_FOR_0, W0    ; Return the corresponding value;

RESET:
    ; If couter is still in reset time...
    add	    #(NUMBER_OF_RESET_BITS - 2), W1
    cp	    W0, W1
    bra	    LE, RESET_EXIT   ; ... keep counting.
    
    ; If reset time is over...
    mov	    #0, W0	     ; ... put back the counter to zero

RESET_EXIT:
    mov	    W0, _ledsInternalCounter
    retlw   #0, W0