/*
 * capteurInfrarouge.c
 *
 *  Created on: 9 mars 2018
 *      Author: Mathias
 */

#include <msp430.h>
#include "ADC.h"
#include "capteurInfrarouge.h"

void initInfrarouge(){
    P1SEL &= ~(BIT5);
    P1SEL2 &= ~(BIT5);
    P1DIR &= ~(BIT5);// pin 1.5 input
    ADC10AE0 |= BIT5;
}

int obstacle(){
    const int valeurSeuilIR = 350;
    int valeurIR;
        ADC_Demarrer_conversion(5);
        valeurIR = ADC_Lire_resultat();
        if (valeurIR>=valeurSeuilIR){
        valeurIR = 1;
        }
        else{
        valeurIR = 0;
        }
    return valeurIR;
}

/*
 * arreter : arret complet du robot
 */
void arreter()
{
    TA1CCR1 = 0;
    TA1CCR2 = 0;
}



void detacteObstacleEtArreter(){
    int obst = obstacle();
    while(obst == 1) {
        P1OUT |= BIT6;
        arreter();
        delay(1000);
        obst = obstacle();
        //if (obst != 1)
            //avancerVitesse(80);
    }

    P1OUT &= ~BIT6;
}


