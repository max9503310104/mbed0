#include "mbed.h"

#define CENTER_BASE 1500

PwmOut servo1(D9);  // right
PwmOut servo0(D8);  // left
Serial pc(USBTX, USBRX);
DigitalInOut ping(D10);
Timer t;


void servo_control1(int speed){
    servo1 = (CENTER_BASE + speed)/20000.0f;
}

void servo_control0(int speed){
    servo0 = (CENTER_BASE + speed)/20000.0f;
}

int main() {
    int i, j, k;
    int move; // 0:front, 1:back, 2:right, 3:left;
    int move_state;
    float ping_val, ping_d;
    int wall_d;
    servo0.period(.02);
    servo1.period(.02);

    move = 0;
    move_state = 0;
    wall_d = 16;
    while(1) {  
        // forward  L98     R-22
        // backward L-100   R27

        // left90
        /*for (i = 0; i < 5; i++) {
            servo_control0(0);
            servo_control1(-35);
            wait(0.21);
            servo_control0(-50);
            servo_control1(0);
            wait(0.17);
        }*/
        // right90
        /*for (i = 0; i < 5; i++) {
            servo_control0(60);
            servo_control1(0);
            wait(0.17);
            servo_control0(0);
            servo_control1(40);
            wait(0.2);
        }*/

        //**************************************************************
        if (move == 0) {
            servo_control0(100);
            servo_control1(-27);
        }
        if (move == 1) {
            servo_control0(0);
            servo_control1(0);
            wait(0.1);
            servo_control0(-100);
            servo_control1(27);
            wait(2);
            move_state++;
            move = 0;
        }
        if (move == 2) {
            servo_control0(0);
            servo_control0(0);
            wait(0.3);
            servo_control0(100);
            servo_control1(10);
            wait(1.41);
            
            /*for (i = 0; i < 7; i++) {
                //servo_control0(45);
                //servo_control1(0);
                //wait(0.3);
                //servo_control0(0);
                servo_control1(18);
                wait(0.15);
                servo_control1(0);
                wait(0.15);
            }*/
            move_state++;
            move = 0;
            
        }
        if (move == 3) {
            servo_control0(0);
            servo_control0(0);
            wait(0.3);
            servo_control0(-25);
            servo_control1(-27);
            wait(1.48);

            /*for (i = 0; i < 7; i++) {
                //servo_control0(-45);
                //servo_control1(0);
                //wait(0.3);
                //servo_control0(0);
                servo_control0(-45);
                wait(0.15);
                servo_control0(0);
                wait(0.15);
            }*/
            move_state++;
            move = 0;
            
        }

        // measure distance
        ping.output();
        ping = 0; wait_us(10);
        ping = 1; wait_us(5);
        ping = 0; wait_us(5);
        ping.input();
        while(ping.read()==0);
        t.start();
        while(ping.read()==1);
        ping_val = t.read();
        ping_d = ping_val * 17700;


        if (ping_d < wall_d) {
            if (move_state == 0) {
                move = 3;
            }
            switch (move_state) {
                case 0: move = 3; break;    // L
                case 1: move = 2; break;    // R
                case 2: move = 1, wall_d = 32; break;    // B
                case 3: move = 2, wall_d = 16; break;    // R
                case 4: move = 3; break;    // L
                case 5: move = 2, wall_d = 32; break;    // R
                case 6: move = 2, wall_d = 16; break;    // R
                case 7: move = 2; break;    // R
                case 8: move = 2; break;    // R
            }
            printf("state = %d\r\n", move_state);
        }

        printf("Ping = %lf\r\n", ping_d);
        t.stop();
        t.reset();
        wait(0.05);
        
    }
}