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
void  position(int r){//selection position du servomoteur
    int rotation=0;
   rotation = slot(1,&spirxtrame);//recupération de la 1er valeur dans la trame spi reçu

    /*     0:0
         * 1:22.5
         * 2:45
         * 3:67.5
         * 4:90
         * 5:112.5
         * 6:135
         * 7:157.5
         * 8:180
         */

    switch(rotation){//9 positions du servo
                    case 0:{
                        TACCR1 = 500;
                        break;
                           }

                    case 1:{
                        TACCR1 = 750;
                        break;
                           }
                    case 2:{
                        TACCR1 = 1000;
                        break;
                         }

                     case 3:{
                         TACCR1 = 1250;
                         break;
                         }
                     case 4:{
                         TACCR1 = 1500;
                         break;
                         }

                     case 5:{
                         TACCR1 = 1750 ;
                         break;
                         }

                     case 6:{
                         TACCR1 = 2000;
                         break;
                         }

                     case 7:{
                         TACCR1 = 2250 ;
                         break;
                         }
                     case 8:{
                         TACCR1 = 2500;
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


        //P1DIR |= BIT6;
        //P1SEL |= BIT6;

        //sortie de la pwm sur p2.6 (xin)
        P2SEL |= BIT6;//P2DIR BIT6 a 1 pour mettre output
        P2DIR |= BIT6;// selection fonction Timer1_A3.TA1


        BCSCTL3 |= (BIT5|BIT4);//D'apres la datasheet pour utiliser ta0.1 il faut que BCSCTL3.LFXT1Sx = 11

        TACTL = TASSEL_2 | ID_0; // source SMCLK pour le timer, mode UP, 2 times divider
        TACCTL1 |= OUTMOD_7; // activation mode de sortie 7 (PWM)

        TACCR0 = 20000;
        TACCR1 = 1500;
        TACTL |= MC_1; //demarre le PWM
}
