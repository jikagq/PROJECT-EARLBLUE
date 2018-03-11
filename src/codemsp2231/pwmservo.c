/*
 * pwmservo.c
 *
 *  Created on: 7 mars 2018
 *      Author:  Mathias Martinez
 */




/*
 * main.c
 */

#include <msp430.h>

#include "main.h"
#include "util.h"
#include "pwmservo.h"
#include "spi2231.h"


int Conv_angle_position (int pas)
{
    int angle = 1;
    int i;
    TACCR1 = 500;
    for (i = 1; i<181; i=i+pas)
    {
        //angle =;
        delay (2000);
    }

}


void initpwmservo(void) {


    P1DIR |= BIT2;                     //P1DIR BIT0 a 1 pour mettre output
    P1SEL |= BIT2;      // selection fonction Timer1_A3.TA1


    TACTL = TASSEL_2 | ID_0; // source SMCLK pour le timer, mode UP, 2 times divider
    TACCTL1 |= OUTMOD_7; // activation mode de sortie 7 (PWM)

    TACCR0 = 20000;
    TACCR1 = 500;


    TACTL |= MC_1; //demarre le PWM


 do
 {
   /* if (TACCR1 == 2500)
        {
            TACCR1 = 500;
            delay (2000);
        }
        else
        {
            TACCR1 = 2500;
            delay (2000);
        }*/
     //Conv_angle_position (20);

     TACCR1 = 500;
     delay (2000);
     TACCR1 = 1000;
     delay (2000);
     TACCR1 = 1500;
     delay (2000);
     TACCR1 = 2000;
     delay (2000);
     TACCR1 = 2500;
     delay (2000);


 }while (1);
}
