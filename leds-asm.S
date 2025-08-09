    .text
    .global _ledsGetPWMDutyCycle
    
_ledsGetPWMDutyCycle:
    ; Load the counter
    mov	    _ledsInternalCounter, W0
    ; Increment the counter, but set it aside
    inc	    W0, W3
    
    ; If counter is over the number of bits to transmit...
    mov	    #120, W4 ; 5 lamps x 3 leds each lamp x 8 bits each led
    cp	    W3, W4 
    bra	    GT, RESET ; ... then it's reset time.

ACTIVE:
    asr	    W0, #3, W1
    mov	    #_display, W2
    add	    W1, W2, W2
    mov.b   [W2], W1
    
    and	    #7, W0
    sl	    W1, W0, W1
    and	    #128, W1
    
    bra	    Z, ACTIVE_ZERO
ACTIVE_ONE:
    mov	    #40, W0
    bra	    ACTIVE_EXIT
ACTIVE_ZERO:
    mov	    #10, W0

ACTIVE_EXIT:
    mov	    W3, _ledsInternalCounter
    return

RESET:
    mov	    #169, W4 ; 120 + 50 for large reset time
    cp	    W3, W4
    bra	    LE, RESET_EXIT
    mov	    #0, W3

RESET_EXIT:
    mov	    W3, _ledsInternalCounter
    mov	    #0, W0
    return