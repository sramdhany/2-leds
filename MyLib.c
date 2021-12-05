// Sarah Ramdhany
// MyLib.c
// ver 9

#include<stdio.h>
#include<stdlib.h>

#include<bcm2835.h>

extern int readButtonPress(int pin)
{
        uint8_t value = bcm2835_gpio_lev(pin);
        switch(value)
        {
                case 0:
                        return 1;
                case 1:
                        return 0;
        }

}