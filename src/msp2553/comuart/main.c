//------------------------------------------------------------------------------
// msp2553 uart
//
//
//
//
//------------------------------------------------------------------------------
#include <msp430g2553.h>
#include <msp430.h>

#include "main.h"
#include "util.h"
#include "uart.h"
#include "spi2553.h"

#define TAILLETRAME 16 //taille de la trame
#define TAILLEVAL 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEUR 4 //nombre de valueur a transmettre

volatile unsigned int i;
volatile int unsigned rxbuffer=0;
volatile char rxtrame[TAILLETRAME];
int onoffled1=0;
int tpsh=1000;
int tpsb=500;
int compteurtrameinutile=0;

//int val=0;
//char str[] = "1000";

void interpreteur(){
   char rxcar;
   rxcar=rxtrame[0];//recup du 1er carac reprsentant l'opération

   switch(rxcar){
      case 'c':{//ping
            pong();
            raztrame();
            break;
            }
      case 'L':{
            led1();
            raztrame();
            break;
            }
      case 't':{
            anvil();
            raztrame();
            break;
            }
      default :{
            nak();
            raztrame();
            break;
            }
      }
}

void anvil(){//gestion des trames forge
    char action;

    action=rxtrame[2];
    switch(action){
          case 'l':{
                ledspi();
                raztrame();
                break;
                }
          case 'a':{
                raztrame();
                break;
                }
          case 'r':{
                raztrame();
                break;
                }
          case 'd':{
                raztrame();
                break;
                }
          case 'g':{
                raztrame();
                break;
                }
          case 'b':{
                raztrame();
                break;
                }
          case 'm':{
                raztrame();
                break;
                }
          default :{
                raztrame();
                break;
                }
          }
    raztrame();
}

ledspi(){
    int etat = 0;
    int frequence = 1000;

    etat = slot(1);
    frequence = slot(2);
}

int slot(int slotnumber){
    int i;
    int var=0;
    int cptseparateur=0;
    int pos=0;//0:gauche 1:droite
    int debut;
    int fin;
    char subsstr[6];

    for(i=3;i<TAILLETRAME-1;i++){//fin de l'entete forge à 3
        if(rxtrame[i]==';'){//;gauche
            if(pos==0){
               pos=1;
               debut=i;
               cptseparateur++;
            }else{//;droit
               pos=0;
               fin=i;
               if(cptseparateur == slotnumber){
                //coupe
                  // var = atoi(str);//convertir les char* en int
               }//sinon rien
            }












        }
    }
   return var;
}

void substringsemicolon(int debut,int fin, char *dest){

}



void led1(){
   if(rxtrame[1]=='1'){
       ack();
       onoffled1=1;
   }
   if(rxtrame[1]=='0'){
       ack();
       onoffled1=0;
   }
   if((rxtrame[1] != '1') && (rxtrame[1] != '0')){
        nak();
   }
   raztrame();

}



void raztrame(){
    for(rxbuffer=0;rxbuffer<16;rxbuffer++){//ini de la trame rx
        rxtrame[rxbuffer]=" ";
    }
    rxbuffer=0;
}





void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT


    if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
    {
        __bis_SR_register(LPM4_bits); // Low Power Mode #trap on Error
    }
    else
    {
        // Factory parameters
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = CALDCO_1MHZ;
    }


    InitUART();

    __bis_SR_register(GIE); // interrupts enabled

    P1DIR |= BIT0;                  // configure P1.0 as output
    P1DIR |= BIT6;

    P1OUT &= ~BIT0;                  // configure P1.0 as output
    P1OUT &= ~BIT6;

    raztrame();
    rxbuffer=0;

    while(1){

        if(onoffled1 == 1){
            //char chainedebug[] = "ici";//texte de debug
            //debug(&chainedebug,46);//données à debug en uart
            P1OUT |= BIT0;
            delay(tpsh);
            P1OUT &= ~BIT0;
            delay(tpsb);
        }else{
           P1OUT &= ~BIT0;
        }


       /** if(val == 1000){
            P1OUT |= BIT0;
            TXdata('c');
            delay(tpsh);
            P1OUT &= ~BIT0;
            delay(tpsb);
        }**/
        //TXdata('c');

    }
    return 0;
}




#pragma vector=USCIAB0RX_VECTOR//reception d'une trame
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c;
    c = UCA0RXBUF;

    P1OUT ^= BIT6;//debug


   /** if(rxbuffer==TAILLETRAME){//secu pour pas dépasser la taille max de la trame
        rxbuffer=0;
   }**/

    if(c == '\0'){//fin de la trame
        rxtrame[rxbuffer]=c;
        //TXdata('c');
        //TXdata(rxtrame[0]);//renvoie le 1er carac pour debug
        if(rxtrame[0]=='f'){//trame forge -> parser
            anvil();
        }else{
            interpreteur();
        }
    }else{//sinon on ajoute le caractaire à la chaine
       rxtrame[rxbuffer]=c;
       rxbuffer++;
    }

}



