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
#include "scan.h"


volatile int valgauche=0;
volatile int valdroite=0;



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

    //config odomètres
    P2DIR  &= ~(BIT0|BIT3);//p2.0 et p2.3 en entrée

    P2IE |= BIT3;//config interruptions p2.3
    P2IES |= BIT3;
    P2IFG &= ~(BIT3);

    P2IE |= BIT0;//config interruptions p2.0
    P2IES |= BIT0;
    P2IFG &= ~(BIT0);

    valgauche=0;
    valdroite=0;




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

void droiteauto(int pas){
    __enable_interrupt();
    while(valdroite<pas){
        TA1CCR1 =100;  //demarrage moteur A
        TA1CCR2 =0;   //demarrage moteur B
    }
    stop();
    valdroite=0;
    __disable_interrupt();
}
/*
 * 50->90°
 * 90->180°
 */
void gaucheauto(int pas){
    __enable_interrupt();
    while(valgauche<pas){
        TA1CCR1 =0;  //demarrage moteur A
        TA1CCR2 =100;   //demarrage moteur B
    }
    stop();
    valgauche=0;
    __disable_interrupt();
}
//interruption odomètre
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR( void){

    if((P2IN & BIT3)==0){
        valgauche++;
        P2IFG &= ~(BIT3);
    }
    if((P2IN & BIT0)==0){
        valdroite++;
       P2IFG &= ~(BIT0);
    }

}
