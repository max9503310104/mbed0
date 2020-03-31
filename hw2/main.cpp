#include "mbed.h"

Serial pc(USBTX, USBRX);
AnalogIn Ain_0(A0);
AnalogOut Aout(DAC0_OUT);
DigitalIn button(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0xFF};


int main() {
    int i, t;
    int half_period = 0;
    int seven_seg_LED[3];
    int sample = 512;
    float Ain;
    float AinData[512];
    int frequency;

    redLED = 1;
    greenLED = 0;
    for (i = 0; i < sample; i++) {
        Ain = Ain_0;
        AinData[i] = Ain;
        wait(1.0 / sample);
    }
    for (i = 1; i < sample; i++) {
        if ((AinData[i] > 0.303 && AinData[i - 1] <= 0.303) || 
            (AinData[i] <= 0.303 && AinData[i - 1] > 0.303)) {          
            half_period++;
        }
    }
    frequency = half_period / 2;
    seven_seg_LED[2] = frequency / 100;
    seven_seg_LED[1] = (frequency / 10) % 10;
    seven_seg_LED[0] = frequency % 10;

    t = 0;
    i = 0;
    while (1) {
        Aout = 0.5 + 0.5*sin(t / 2048.0 * frequency * 6.2832);
        t++;
        wait(1.0 / 2048);
        
        if (button == 0) {
            redLED = 0;
            greenLED = 1;
            display = table[seven_seg_LED[2]];
            for (i = 0; i < 170; i++) {
                pc.printf("%1.3f\r\n",AinData[i]);
                wait(1.0 / 170);
            }
            display = table[seven_seg_LED[1]];
            for (i = 170; i < 340; i++) {
                pc.printf("%1.3f\r\n",AinData[i]);
                wait(1.0 / 170);
            }
            display = table[seven_seg_LED[0]];
            display[7] = 1;
            for (i = 340; i < 512; i++) {
                pc.printf("%1.3f\r\n",AinData[i]);
                wait(1.0 / 170);
            }
        } else {
            redLED = 1;
            greenLED = 0;
            display = table[11];
        }
    }
}