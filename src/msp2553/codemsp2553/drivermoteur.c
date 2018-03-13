/*
 * drivermoteur.c
 *
 *  Created on: 9 mars 2018
 *      Author: theo-
 */

#include <msp430g2553.h>
#include <msp430.h>

#include "main.h"
#include "util.h"
#include "uart.h"
#include "spi2553.h"
#include "drivermoteur.h"

void initmoteur(void){
    BCSCTL1=CALBC1_1MHZ;
    DCOCTL=CALDCO_1MHZ;

    P2DIR |= (BIT5|BIT1|BIT2|BIT4);

    P2OUT &=~ (BIT1);//sens normal, moteur A
       P2OUT |= (BIT5);//sens normal, moteur B


    P2SEL |=(BIT2|BIT4);
    P2SEL2 &=~(BIT2|BIT4);
    TA1CTL=TASSEL_2 | MC_1;
    TA1CCTL1|= OUTMOD_7;
    TA1CCTL2|= OUTMOD_7;
    TA1CCR0=210;

    //TA1CCR1 =100;  //demarrage moteur A
   // TA1CCR2 =0;   //demarrage moteur B
}

void avancer(void){
    P2OUT &=~ (BIT1);//sens normal, moteur A
    P2OUT |= (BIT5);//sens normal, moteur B
    TA1CCR1 =100;  //demarrage moteur A
    TA1CCR2 =100;   //demarrage moteur B
}

void reculer(void){
    P2OUT |=  (BIT1);//sens inverse, moteur A
    P2OUT &=~ (BIT5);//sens inverse, moteur B
    TA1CCR1 =100;  //demarrage moteur A
    TA1CCR2 =100;   //demarrage moteur B
}

void droite(void){
    TA1CCR1 =100;  //demarrage moteur A
    TA1CCR2 =0;   //demarrage moteur B
}
void gauche(void){
    TA1CCR1 =0;  //demarrage moteur A
    TA1CCR2 =100;   //demarrage moteur B
}
void stop(void){
    TA1CCR1 =0;  //demarrage moteur A
    TA1CCR2 =0;
}
void testmoteur(void){
    initmoteur();
    avancer();
    delay(5000);
    stop();
    droite();
    delay(2500);
    stop();
    gauche();
    delay(2500);
    stop();
    reculer();
    delay(5000);
    stop();
}
