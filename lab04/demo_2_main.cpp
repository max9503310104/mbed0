#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

int main()
{
    uLCD.background_color(0xFFFFFF);
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.cls();

    uLCD.color(0x0000FF);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.locate(0,1);
    uLCD.printf("107061103");

    uLCD.color(0x00FF00);
    uLCD.text_width(4);
    uLCD.text_height(4);
    uLCD.locate(1,2);
    for (int i = 30; i >= 0; i--) {
        uLCD.locate(1,2);
        uLCD.printf("%2d", i);
        wait(1);
    }
}
