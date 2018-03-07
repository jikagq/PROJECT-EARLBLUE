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

volatile unsigned int i;

int onoffled1=0;
int tpsh=1000;
int tpsb=500;
int compteurtrameinutile=0;



void ledspi()
{
	int i;
    int etat = 0;
    int frequence = 500;
    char trame_SPI[TAILLETRAMESPI];
    int dataint[NOMBREDEVALEURSPI];

    etat = slotuart(1);//recupération des variable en entier arrivant de l'uart
    frequence = slotuart(2);

    dataint[0]=etat;//remplissage tableau de donnée à transmettre en spi
    dataint[1]=frequence;

    forgespi(2,'l',&dataint,&trame_SPI);//forgage de la trame spi à transmettre
    send_SPI(&trame_SPI);//envoi de la trame spi
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
    Init_SPI();

    __bis_SR_register(GIE); // interrupts enabled

    P1DIR |= BIT0;                  // configure P1.0 as output
    P1OUT &= ~BIT0;                  // configure P1.0 as output


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

}





