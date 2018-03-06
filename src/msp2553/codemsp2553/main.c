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

#define TAILLETRAMEUART 16 //taille de la trame
#define TAILLEVALUART 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEURUART 4 //nombre de valueur a transmettre

#define TAILLETRAMESPI 16 //taille de la trame
#define TAILLEVALSPI 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEURSPI 4 //nombre de valueur a transmettre



volatile unsigned int i;
volatile int unsigned rxbufferuart=0;
volatile char rxtrameuart[TAILLETRAMEUART];
int onoffled1=0;
int tpsh=1000;
int tpsb=500;
int compteurtrameinutile=0;

void interpreteuruart(){
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
      case 't':{
            anvil();
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

void anvil(){//gestion des trames forge
    char action;
    action=rxtrameuart[2];
    switch(action){
          case 'l':{
                ledspi();
                raztrameuart();
                break;
                }
          case 'a':{
                raztrameuart();
                break;
                }
          case 'r':{
                raztrameuart();
                break;
                }
          case 'd':{
                raztrameuart();
                break;
                }
          case 'g':{
                raztrameuart();
                break;
                }
          case 'b':{
                raztrameuart();
                break;
                }
          case 'm':{
                raztrameuart();
                break;
                }
          default :{
                raztrameuart();
                break;
                }
          }
    raztrameuart();
}


void ledspi()
{
	int i;
    int etat = 0;
    int frequence = 500;
    char trame_SPI[TAILLETRAMESPI];
    int dataint[NOMBREDEVALEURSPI];

    etat = slot(1);//recupération des variable en entier arrivant de l'uart
    frequence = slot(2);

    dataint[0]=etat;//remplissage tableau de donnée à transmettre en spi
    dataint[1]=frequence;

    forge(2,'l',&dataint,&trame_SPI);//forgage de la trame spi à transmettre
    //sendspi(&trame_SPI);//envoi de la trame spi
}

int slot(int slotnumber){
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
                   var=substringsemicolon(debut, fin);
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

int substringsemicolon(int debut,int fin){
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
}



void led1(){
   if(rxtrameuart[1]=='1'){
       ack();
       onoffled1=1;
   }
   if(rxtrameuart[1]=='0'){
       ack();
       onoffled1=0;
   }
   if((rxtrameuart[1] != '1') && (rxtrameuart[1] != '0')){
        nak();
   }
   raztrameuart();

}



void raztrameuart(){
    for(rxbufferuart=0;rxbufferuart<16;rxbufferuart++){//ini de la trame rx
        rxtrameuart[rxbufferuart]=" ";
    }
    rxbufferuart=0;
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
    P1OUT &= ~BIT0;                  // configure P1.0 as output
    raztrameuart();
    rxbufferuart=0;

    while(1){
        if(onoffled1 == 1){
            P1OUT |= BIT0;
            delay(tpsh);
            P1OUT &= ~BIT0;
            delay(tpsb);
        }else{
           P1OUT &= ~BIT0;
        }
    }
    return 0;
}




#pragma vector=USCIAB0RX_VECTOR//reception d'une trame
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c;
    c = UCA0RXBUF;
    if(c == '\0'){//fin de la trame
        rxtrameuart[rxbufferuart]=c;
        if(rxtrameuart[0]=='f'){//trame forge -> parser
            anvil();
        }else{
            interpreteuruart();
        }
    }else{//sinon on ajoute le caractaire Ã  la chaine
       rxtrameuart[rxbufferuart]=c;
       rxbufferuart++;
    }

}
