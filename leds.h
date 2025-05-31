#ifndef LEDS_H
#define	LEDS_H

#define NUMBER_OF_RESET_BITS 50
#define NUMBER_OF_PIXELS 5

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef Pixel Display[NUMBER_OF_PIXELS];

/**
 * Initializes the LEDs.
 */
void ledsInitialize();

/**
 * Sets the position of the light
 * @param position A integer between 0 and 4095
 */
void ledsSetPosition(int position);

/**
 * State machine returning the DC to use when producing the PWM to control
 * the chain of indexable LEDs.
 * @return The duty cycle to use.
 */
int ledsGetPWMDutyCycle();

#ifdef TEST
void testLeds();
#endif

#endif /* LEDS_H */