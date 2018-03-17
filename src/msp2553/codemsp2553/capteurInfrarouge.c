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
    P1SEL &= ~(BIT3);
    P1SEL2 &= ~(BIT3);
    P1DIR &= ~(BIT3);// pin 1.3 input
    ADC10AE0 |= BIT3;
}

int obstacle(){
    int valeurIR=0;
        ADC_Demarrer_conversion(3);
        valeurIR = ADC_Lire_resultat();
        if (valeurIR>=SEUILOBSTACLE){
            valeurIR = 1;//=obs
        }
        else{
            valeurIR = 0;
        }
    return valeurIR;
}

int aquisition(){
    int valeurIR=0;
            ADC_Demarrer_conversion(3);
            valeurIR = ADC_Lire_resultat();

       return valeurIR;
}


