/*
 * spi2231.c
 *
 *  Created on: 8 mars 2018
 *      Author: theo-
 */
#include <msp430g2231.h>
#include <msp430.h>

#include "main.h"
#include "util.h"
#include "pwmservo.h"
#include "spi2231.h"


volatile int unsigned spirxbuffer=0;
volatile char spirxtrame[TAILLETRAMESPI];

#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)//interruption spi rx
{
    unsigned char c;
    c = USISRL;
        if(c == '\0'){//fin de la trame
            spirxtrame[spirxbuffer]=c;
            anvilspi();
        }else{//sinon on ajoute le caractaire � la chaine
           spirxtrame[spirxbuffer]=c;
           spirxbuffer++;
        }
     USISRL = P1IN;
     USICNT = 8;
}
void anvilspi(void){//gestion des trames forge
    char action;

    action=spirxtrame[2];
    switch(action){
          case 'l':{
                ledparam();
                raztrame(&spirxtrame);
                break;
                }
          default :{
                raztrame(&spirxtrame);
                break;
                }
          }
    raztrame(&spirxtrame);
}

void ledparam(void){

    etat = slot(1,&spirxtrame);
    freq = slot(2,&spirxtrame);

}
void SendSpislave(char c){

    USISRL = c;
    USICNT = 8;
}
void SendSpitrameslave(char *data){
    int i =0;
    while(data != '\0'){
        SendSpislave(data[i]);
        i++;
    }
}
void initSPI(void){
    P1OUT =  0x10;                        // P1.4 set, else reset
    P1REN |= 0x10;                        // P1.4 pullup
    P1DIR = 0x01 ;                         // P1.0 output, else input
    USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIOE; // Port, SPI slave p406
      //USIPE7 sdi 1
      //USIPE6 sdo 1
      //USIPE5 clk 1
      //USIOE Data output enable 1
    USICTL1 |= USIIE;                     // Counter interrupt, flag remains set p407
    USICTL0 &= ~USISWRST;                 // USI released for operation p406
    USISRL = P1IN;                        // init-load data p409
    USICNT = 8;                           // init-load counter nb de bit p408

    _BIS_SR(LPM0_bits + GIE);             // Enter LPM0 w/ interrupt

}
