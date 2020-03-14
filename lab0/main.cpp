#include "mbed.h"

int main()
{
    DigitalOut redLED = LED_RED;
    DigitalOut greenLED = LED_GREEN;
    int i;

    redLED = 1;
    greenLED = 1;
    while (1) {
        for (i = 0; i < 6; i++) {
            redLED = !redLED;
            wait(0.2f);
        }
        for (i = 0; i < 4; i++) {
            greenLED = !greenLED;
            wait(0.2f);
        }

    }
}


