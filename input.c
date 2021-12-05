// Sarah Ramdhany
// input.c
// ver 9
//
// Example program for bcm2835 library
// Reads and prints the state of an input pin
//
// After installing bcm2835, you can build this
// with something like:
// gcc -o input input.c -l bcm2835
// sudo ./input
//
// Or you can test it before installing with:
// gcc -o input -I ../../src ../../src/bcm2835.c input.c
// sudo ./input
//
// Author: Mike McCauley
// Copyright (C) 2011 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include "MyLib.h"

// Input on RPi Plug P1 pin 11 (which is GPIO pin 17)
#define PIN RPI_GPIO_P1_11

// Input on RPi Plug P1 pin 12 (which is GPIO pin 18)
#define LED1 RPI_GPIO_P1_12

// Input on RPi Plug P1 pin 16 (which is GPIO pin 23)
#define LED2 RPI_GPIO_P1_16

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
//    bcm2835_set_debug(1);

    if (!bcm2835_init())
        return 1;

    // Set RPI pin P1-11 to be an input
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    //  with a pullup
    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);

    // Set the pin to be an output
    bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);

    // Set the pin to be an output
    bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);

    //Initialize
    int pressedFlag = 0; // 0 if not pressed.  1 is pressed
    int total = 0;

    // Blink
    while (1)
    {
        // Read some data
        pressedFlag = readButtonPress(PIN);

        if(pressedFlag)  //if bcm2835_gpio_lev(PIN) == 0, then button is pressed.  1 means button is released.
        {
            printf("Button was pressed\n");
            printf("Button was released\n");
            total += pressedFlag;
            printf("Button was pressed a total of %d time(s)\n", total);
            switch(total % 4)
            {
                case 0:
                    printf("00\n");
                    bcm2835_gpio_write(LED1, LOW);
                    bcm2835_gpio_write(LED2, LOW);
                    break;
                case 1:
                    printf("01\n");
                    bcm2835_gpio_write(LED1, HIGH);
                    bcm2835_gpio_write(LED2, LOW);
                    break;
                case 2:
                    printf("10\n");
                    bcm2835_gpio_write(LED1, LOW);
                    bcm2835_gpio_write(LED2, HIGH);
                    break;
                case 3:
                    printf("11\n");
                    bcm2835_gpio_write(LED1, HIGH);
                    bcm2835_gpio_write(LED2, HIGH);
                    break;
            }
        }

        // wait a bit
        delay(500);
    }

    bcm2835_close();
    return 0;
}