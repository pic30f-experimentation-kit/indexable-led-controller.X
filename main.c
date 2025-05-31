#include "shared.h"

#include "peripheral-adc.h"
#include "peripheral-pwm.h"
#include "test.h"
#include "buffer.h"
#include "leds.h"

#include <xc.h>

#pragma config FOSC_FOSFPR = FRC_PLL16     // FRC w/PLL 16x 
#pragma config FOSC_FCKSMEN = CSW_FSCM_OFF // Sw Disabled, Mon Disabled 
#pragma config FICD_ICS = ICS_PGD          // Use PGC/EMUC and PGD/EMUD
#pragma config FWDT_WDT = WDT_OFF          // Disable watchdog

#ifndef TEST

int main() {
    // Initialization of variables
    bufferInitialize(&capturesBuffer);
    ledsInitialize();
    ledsSetPosition(0);

    // Initialization of modules
    initializePWM();
    initializeADC();
    
    // Forever...
    for(;;) {
        // Wait for data in the buffer:
        while(bufferIsEmpty(&capturesBuffer));
        
        // Process the data:
        ledsSetPosition(bufferRead(&capturesBuffer));
    }
}

#else
int main() {
    testInitialize();
    testBuffer();
    testLeds();
    testReport();
    while(1);
}
#endif
