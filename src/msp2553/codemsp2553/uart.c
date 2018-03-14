/*
 * uart.c
 *
 *  Created on: 3 mars 2018
 *      Author: theo-
 */

#include <msp430g2553.h>
#include <msp430.h>

#include "main.h"
#include "util.h"
#include "uart.h"
#include "spi2553.h"

volatile int unsigned indexrxbufferuart=0;
volatile char rxtrameuart[TAILLETRAMEUART];

#pragma vector=USCIAB0RX_VECTOR//reception d'une trame
__interrupt void USCI0RX_ISR(void)//interruption permettant de recevoir un cararctere et de l'ajpouter au buffer
{
    unsigned char c;
    c = UCA0RXBUF;
    if(c == '\0'){//fin de la trame
        rxtrameuart[indexrxbufferuart]=c;
        if(rxtrameuart[0]=='f'){//trame forge -> parser
            anviluart();
        }else{
            interpreteuruart();
        }
    }else{//sinon on ajoute le caractaire Ã  la chaine
       rxtrameuart[indexrxbufferuart]=c;
       indexrxbufferuart++;
    }

}
void interpreteuruart(void){//analyse des commandes venant de codeblock en mode interpreteur (old)
   char rxcar;
   rxcar=rxtrameuart[0];//recup du 1er carac reprsentant l'opÃ©ration

   switch(rxcar){
      case 'c':{//ping
            pong();
            raztrameuart();
            break;
            }
      case 'L':{
            led1();
            raztrameuart();
            break;
            }
      case 't':{//bypass hasardeux
            anviluart();
            raztrameuart();
            break;
            }
      default :{
            nak();
            raztrameuart();
            break;
            }
      }
}

void anviluart(void){//gestion des trames forge venant du pc puis apres du blutooth
    char action;
    action=rxtrameuart[2];//recupération de l'action a faire dans la trame forge (pour le protocole voir le readme quand ce sera écrit)
    switch(action){//ici mettre les actions que le 2553 va faire lorqu il recevra une trame en uart l'uart
          case 'l':{
                ledspi();//led en spi sur 2231
                raztrameuart();
                break;
                }
          case 'L':{
                led();
                raztrameuart();
                TXdata(0x06);
                break;
                }
          case 'a':{//avancer
                raztrameuart();
                avancer();
                TXdata(0x06);
                break;
                }
          case 'r':{//reculer
                raztrameuart();
                reculer();
                TXdata(0x06);
                break;
                }
          case 'd':{
                raztrameuart();
                droite();
                TXdata(0x06);
                break;
                }
          case 'g':{
                raztrameuart();
                gauche();
                TXdata(0x06);
                break;
                }
          case 's':{
                stop();
                raztrameuart();
                TXdata(0x06);
                break;
                }
          case 'm':{ //mode
                TXdata(0x06);//ack=0x06 ascii
                changemode();
                raztrameuart();
                break;
                }
          case 't':{
                raztrameuart();
                testmoteur();
                TXdata(0x06);
                break;
                }
          default :{//renvoyer quleque chose si trame pas compris
                nak();
                raztrameuart();
                break;
                }
          }
    raztrameuart();
}
void raztrameuart(void){//raz de la trame uart
    int index=0;
    for(index=0;index<TAILLETRAMEUART;index++){//ini de la trame rx
        rxtrameuart[index]=" ";
    }
    indexrxbufferuart=0;
}
void InitUART(void)//initialisation de la com uart
{
    P1SEL |= (BIT1 | BIT2);                     // P1.1 = RXD, P1.2=TXD
        P1SEL2 |= (BIT1 | BIT2);                    // P1.1 = RXD, P1.2=TXD
        UCA0CTL1 = UCSWRST;                         // SOFTWARE RESET
        UCA0CTL1 |= UCSSEL_3;                       // SMCLK (2 - 3)

        UCA0CTL0 &= ~(UCPEN | UCMSB | UCDORM);
        UCA0CTL0 &= ~(UC7BIT | UCSPB | UCMODE_3 | UCSYNC); // dta:8 stop:1 usci_mode3uartmode
        UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**

        UCA0BR0 = 104;                              // 1MHz, OSC16, 9600 (8Mhz : 52) : 8/115k
        UCA0BR1 = 0;                                // 1MHz, OSC16, 9600
        UCA0MCTL = 10;

        /* Enable USCI_A0 RX interrupt */
        IE2 |= UCA0RXIE;

        raztrameuart();//ini de la trame
        indexrxbufferuart=0;

       // volatile char test[5];
        //volatile int nombtre[5];
        //forge(2,'a', &nombtre, &test);
}

void TXdata( unsigned char c )//envoi d'un caractère via l'uart
{
    //P1OUT ^= BIT6;//debug
    while (!(IFG2&UCA0TXIFG));  // USCI_A0 TX buffer ready?
    UCA0TXBUF = c;              // TX -> RXed character
}

void pong(void){
    unsigned int i;
    char pong[] = "pong";
    for(i=0;i<5;i++){
        TXdata(pong[i]);
    }

}

void ack(void){
    unsigned int i;
    char ack[] = "ack";
    for(i=0;i<4;i++){
        TXdata(ack[i]);
    }
}
void nak(void){
    unsigned int i;
    char nak[] = "nak";
    for(i=0;i<4;i++){
        TXdata(nak[i]);
    }
}

void debug(char *texte, int valeur){
    int i=0;
    char intenchar[5];

    while(texte[i] != '\0'){
        TXdata(texte[i]);
        i++;
    }
    TXdata(' ');
    itoad(valeur, &intenchar, 10);//conversion d'un entier en chaine

    TXdata('\0');//fin
}


/**int slotuart(int slotnumber){//decodage de la trame uart
    int i;
    int var=0;
    int cptseparateur=0;
    int pos=0;//0:gauche 1:droite
    int debut=0;
    int fin=0;

    for(i=3;i<TAILLETRAMEUART-1;i++){//fin de l'entete forge Ã  3
        if((rxtrameuart[i]==';') || (rxtrameuart[i]=='\0')){//;gauche
            if(pos==0){
               pos=1;
               debut=i;
               cptseparateur++;
            }else{//;droit
               pos=0;
               fin=i;
               if(cptseparateur == slotnumber){
                //coupe
                   var=substringsemicolonuart(debut, fin);
                   i=TAILLETRAMEUART-1;//quite la boucle dÃ¨s que la veleur est extraites pour pas se taper toutes la trame
               }else{
                   pos=1;
                   debut=i;
                   cptseparateur++;
               }
            }
        }
    }
   return var;
}

int substringsemicolonuart(int debut,int fin){//conversion d'une donnée de la trame uart
    char subsstr[6];
    int a=0;
    int b=0;
    int var=-1;


    b=debut;
    while(b<fin){
        subsstr[a]=rxtrameuart[b+1];
        b++;
        a++;
    }
    var = atoi(subsstr);
    return var;
}**/
