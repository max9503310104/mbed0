#include "mbed.h"
#include "TextLCD.h"

DigitalOut led(LED_RED);
TextLCD lcd(D2, D3, D4, D5, D6, D7);

int main()
{
      int x=30;
      lcd.printf("107061103");
      while(true)
      {
            led = !led;             // toggle led
            lcd.locate(5,1);
            lcd.printf("%2i",x);    //conuter display
            wait(1);
            if (x > 0)
                x--;

      }
}