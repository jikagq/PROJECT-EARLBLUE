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


///////////pas testé
void  position(void){//selection position du servomoteur
    int rotation;
   rotation = slot(1,&spirxtrame);//recupération de la 1er valeur dans la trame spi reçu


    switch(rotation){//10 positions du servo
                    case 1:{
                        TACCR1 = 500;
                        delay (2000);// pourquoi des delais ?
                        TACCR1 = 0;
                        break;
                           }

                    case 2:{
                        TACCR1 = 722;
                        delay (2000);
                        TACCR1 = 0;
                        break;
                           }
                    case 3:{
                        TACCR1 = 944;
                        delay (2000);
                        TACCR1 = 0;
                        break;
                         }

                     case 4:{
                         TACCR1 = 1166;
                         delay (2000);
                         TACCR1 = 0;
                         break;
                         }
                     case 5:{
                         TACCR1 = 1388;
                         delay (2000);
                         TACCR1 = 0;
                         break;
                         }

                     case 6:{
                         TACCR1 = 1611;
                         delay (2000);
                         TACCR1 = 0;
                         break;
                         }

                     case 7:{
                         TACCR1 = 1833;
                         delay (2000);
                         TACCR1 = 0;
                         break;
                         }

                     case 8:{
                         TACCR1 = 2055;
                         delay (2000);
                         TACCR1 = 0;
                         break;
                         }
                     case 9:{
                         TACCR1 = 2277;
                         delay (2000);
                         TACCR1 = 0;
                         break;
                         }
                     case 10:{
                         TACCR1 = 2500;
                         delay (2000);
                         TACCR1 = 0;
                         break;
                         }
                     default :{
                         TACCR1 = 0;
                         break;
                         }
                    }
}
/////////////
void initpwmservo(void) {


    P1DIR |= BIT2;                     //P1DIR BIT0 a 1 pour mettre output
        P1SEL |= BIT2;      // selection fonction Timer1_A3.TA1


        TACTL = TASSEL_2 | ID_0; // source SMCLK pour le timer, mode UP, 2 times divider
        TACCTL1 |= OUTMOD_7; // activation mode de sortie 7 (PWM)

        TACCR0 = 20000;
        TACCR1 = 500;
        TACTL |= MC_1; //demarre le PWM
}
