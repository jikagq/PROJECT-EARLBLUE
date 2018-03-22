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

/*
 * pense à ajouter le retour du pont spi
 */

volatile int unsigned spirxbuffer=0;//buffer de reception
volatile char spirxtrame[TAILLETRAMESPI];//tableau de reception def 16

#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)//interruption spi rx
{
    unsigned char c;
    c = USISRL;//incomming carac
    //SendSpislave(c);
        if(c == '\0'){//fin de la trame
            spirxtrame[spirxbuffer]=c;
            anvilspi();
        }else{//sinon on ajoute le caractaire à la chaine
           spirxtrame[spirxbuffer]=c;//tant que y a pas la fin de trame ecriture dans le tableau
           spirxbuffer++;//potentiellment faut ajouter une secu ?
        }
     USISRL = P1IN;// ?
     USICNT = 8;//raz compteur caractèrre
     //USISRL = 0x06; //retour ack
}


void anvilspi(void){//interpreteur des trames forge
    char action;

    action=spirxtrame[2];//le 3eme char correspond à l'action à effectuer

    switch(action){
          case 'l':{
                ledparam();//cli led + freq 2231
                //raztramespi();
                break;
                }
          case 's':{//modification de l'angle du servo
                position(0);

                break;
                }
          default :{
                //raztramespi();
                break;
                }
          }
    raztramespi();
}

void ledparam(void){//modification des var globales liées à la led du 2231

    etat = slot(1,&spirxtrame);//recupération de l entier contenu dans le slot 1 de la trame spi
    freq = slot(2,&spirxtrame);//recupération de l entier contenu dans le slot 2 de la trame spi

}
//////////////pas testé
void SendSpislave(char c){//envoi d'un char en spi

    USISRL = c;
    USICNT = 8;
}
void SendSpitrameslave(char *data){//envoi d'une chaine/trame en spi
    int i =0;
    while(data != '\0'){
        SendSpislave(data[i]);
        i++;
    }
}
//////////////
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
   // _BIS_SR( GIE);             //lpm0_bits bloquait le programme ?
}

void raztramespi(void){//raz trame spi
    int index=0;
     for(index=0;index<TAILLETRAME;index++){//reini de la trame rx
         spirxtrame[index]='\0';
     }
     spirxbuffer=0;//raz buff
}
