#include "leds.h"

#include "peripheral-pwm.h"
#include "test.h"

static Display display;

typedef enum {
    RUN,
    RESET
} LedsEmissionState;

static LedsEmissionState state;
static unsigned char *firstPosition;
static unsigned char *lastPosition;

static unsigned char *position;
static unsigned char mask;
static int resetCounter;
static int nn;

void ledsInitialize() {
    firstPosition = &display[0].r;
    lastPosition = &display[NUMBER_OF_PIXELS - 1].b;
    position = firstPosition;
    mask = 0b10000000;
    state = RUN;
    nn = 0;
}

int ledsGetPWMDutyCycle() {
    if (state == RESET) {
        resetCounter++;
        if (resetCounter >= NUMBER_OF_RESET_BITS) {
            position = firstPosition;
            state = RUN;
        }
        return PWM_DC_FOR_RESET;
    }

    char value = *position & mask;
    mask >>= 1;
    if (mask == 0) {
        position++;
        if (position > lastPosition) {
            resetCounter = 0;
            state = RESET;
        }
        mask = 0b10000000;
    }

    if (value == 0) {
        return PWM_DC_FOR_0;
    }
    return PWM_DC_FOR_1;
}

void ledsSetPosition(int position) {
    float interval = (float) position;
    interval /= 4096;
    interval *= NUMBER_OF_PIXELS - 1;

    int digitA = (int) interval;
    int digitB = digitA + 1;

    interval -= digitA;
    interval *= 255;

    int weightB = (int) interval;
    int weightA = 255 - weightB;

    for(int n = 0; n < NUMBER_OF_PIXELS; n++) {
        if (n == digitA) {
            display[n].r = weightA;
        } else if (n == digitB) {
            display[n].r = weightB;
        } else {
            display[n].r = 0;
        }
    }
}

#ifdef TEST
#include <stdio.h>

void leds_can_provide_duty_cycle_for_the_first_pixel() {
    ledsInitialize();
    display[0].r = 0b10101010;
    display[0].g = 0b11001100;
    display[0].b = 0b11110000;
    
    assertEquals("LED_R7", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_R6", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_R5", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_R4", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_R3", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_R2", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_R1", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_R0", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);

    assertEquals("LED_G7", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_G6", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_G5", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_G4", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_G3", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_G2", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_G1", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_G0", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);

    assertEquals("LED_B7", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_B6", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_B5", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_B4", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
    assertEquals("LED_B3", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_B2", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_B1", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
    assertEquals("LED_B0", ledsGetPWMDutyCycle(), PWM_DC_FOR_0); 
}

void leds_can_provide_duty_cycle_for_all_displays() {
    ledsInitialize();
    for(int n = 0; n < NUMBER_OF_PIXELS; n++) {
        display[n].r = 0b10101010;
        display[n].g = 0b10101010;
        display[n].b = 0b10101010;
    }
    for(int pixel = 0; pixel < NUMBER_OF_PIXELS; pixel++) {
        for(int color = 0; color < 3; color++) {
            assertEquals("LED_D7", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
            assertEquals("LED_D6", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
            assertEquals("LED_D5", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
            assertEquals("LED_D4", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
            assertEquals("LED_D3", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
            assertEquals("LED_D2", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
            assertEquals("LED_D1", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
            assertEquals("LED_D0", ledsGetPWMDutyCycle(), PWM_DC_FOR_0);
        }
    }
}

void leds_can_provide_duty_cycle_for_last_pixel_then_reset_then_first_pixel() {
    ledsInitialize();
    for(int n = 0; n < NUMBER_OF_PIXELS; n++) {
        display[n].r = 255;
        display[n].g = 255;
        display[n].b = 255;
    }
    for(int pixel = 0; pixel < NUMBER_OF_PIXELS; pixel++) {
        for(int color = 0; color < 3; color++) {
            for(int bit = 0; bit < 8; bit++) {
                assertEquals("LED_C", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
            }
        }
    }
    
    for(int n = 0; n < NUMBER_OF_RESET_BITS; n++) {
        if (!assertEquals("LED_Z", ledsGetPWMDutyCycle(), PWM_DC_FOR_RESET)) {
            printf("(Test failed at step %d)\r\n", n);
            break;
        }
    }
    
    assertEquals("LED_CC", ledsGetPWMDutyCycle(), PWM_DC_FOR_1);
}

void leds_can_set_position_at_the_lowest() {
    ledsSetPosition(0);
    assertEquals("LEDS_PR_0", display[0].r, 255);
    assertEquals("LEDS_PR_1", display[1].r, 0);
    assertEquals("LEDS_PR_2", display[2].r, 0);
    assertEquals("LEDS_PR_3", display[3].r, 0);
    assertEquals("LEDS_PR_4", display[4].r, 0);
}

void leds_can_set_position_between_1_and_2() {
    ledsSetPosition(1100);
    assertEquals("LEDS_PR_5", display[0].r, 0);
    assertEquals("LEDS_PR_6", display[1].r, 237);
    assertEquals("LEDS_PR_7", display[2].r, 18);
    assertEquals("LEDS_PR_8", display[3].r, 0);
    assertEquals("LEDS_PR_9", display[4].r, 0);
}

void leds_can_set_position_in_the_middle() {
    ledsSetPosition(2048);
    assertEquals("LEDS_PR_10", display[0].r, 0);
    assertEquals("LEDS_PR_11", display[1].r, 0);
    assertEquals("LEDS_PR_12", display[2].r, 255);
    assertEquals("LEDS_PR_13", display[3].r, 0);
    assertEquals("LEDS_PR_14", display[4].r, 0);
}

void leds_can_set_position_between_2_and_3() {
    ledsSetPosition(2560);
    assertEquals("LEDS_PR_15", display[0].r, 0);
    assertEquals("LEDS_PR_16", display[1].r, 0);
    assertEquals("LEDS_PR_17", display[2].r, 128);
    assertEquals("LEDS_PR_18", display[3].r, 127);
    assertEquals("LEDS_PR_19", display[4].r, 0);
}

// Uncomment the definition below.
// Then, put a break point at first and last call, and use simulator's
// stopwatch to measure the execution time.
// A good solution should spend less than 3500 cycles executing the
// complete for loop.
// #define PERFORMANCE
#ifdef PERFORMANCE
void leds_have_good_performance() {
    ledsInitialize();
    for(int n = 0; n < 10; n++) {
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
        ledsGetPWMDutyCycle();
    }
}
#endif

void testLeds() {
    leds_can_provide_duty_cycle_for_the_first_pixel();
    leds_can_provide_duty_cycle_for_all_displays();
    leds_can_provide_duty_cycle_for_last_pixel_then_reset_then_first_pixel();
    leds_can_set_position_at_the_lowest();
    leds_can_set_position_between_1_and_2();
    leds_can_set_position_in_the_middle();
    leds_can_set_position_between_2_and_3();
#ifdef PERFORMANCE
    leds_have_good_performance();
#endif
}
#endif

