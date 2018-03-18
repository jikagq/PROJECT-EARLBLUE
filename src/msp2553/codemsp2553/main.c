/*
 * code principal msp2553
 *
 *
 *
 *
 */
#include <msp430g2553.h>
#include <msp430.h>

#include "main.h"
#include "util.h"
#include "uart.h"
#include "spi2553.h"
#include "drivermoteur.h"
#include "scan.h"
#include "ADC.h"
#include "capteurInfrarouge.h"

volatile unsigned int i;

int onoffled1=0;//led 2553
int freq=1000;

int mode=0;//mode auto/manu

void ledspi(void)// led 2231 par spi
{
    int dataint[NOMBREDEVALEURSPI];
    //!!!utilisation des fonction generique dans util.c, sauf raz ?

    dataint[0] = slot(1,&rxtrameuart);//recupération des variable en entier arrivant de l'uart
    dataint[1] = slot(2,&rxtrameuart);// préparation des données à transmettre en spi

    raztrameuart();//raz de la trame uart une fois les données extraites

    forge(2,'l',&dataint,&trametx_SPI);//forgage de la trame spi à transmettre
    send_SPI(&trametx_SPI);//envoi de la trame spi
}


void led(void){//led 2553 avec anvil()
    onoffled1 = slot(1,&rxtrameuart);//recupération des variable en entier arrivant de l'uart
    freq = slot(2,&rxtrameuart);
}


void led1(void){//led 2553 avec interpreteur()
   if(rxtrameuart[1]=='1'){
       ack();//renvoi d'un ack au pc
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


void iniboard(void){
    P1DIR = 0x00; // IN high z
    P2DIR = 0x00; // IN

    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT


        if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
        {
            __bis_SR_register(LPM4_bits); // Low Power Mode #trap on Error
        }
        else
        {
            // Factory parameters
            DCOCTL = 0;
            BCSCTL1 = CALBC1_1MHZ;
            DCOCTL = (0 | CALDCO_1MHZ);
        }
}



void main(void)
{
    iniboard();
    InitUART();
    Init_SPI();
 //   testmoteur();
    initmoteur();
    ADC_init();
    initInfrarouge();
    iniservo();

   // positionservo(4);
    //droiteauto(13);
    //gaucheauto(25);
    //avancer();
    //delay(5000);
    //stop();
    __bis_SR_register(GIE); // interrupts enabled

    P1DIR |= BIT0;                  // configure P1.0 as output
    P1OUT &= ~BIT0;                  // configure P1.0 as output


    while(1){
        if(onoffled1 == 1){//cli led
            P1OUT |= BIT0;
            delay(freq);
            P1OUT &= ~BIT0;
            delay(freq);
        }else{
           P1OUT &= ~BIT0;
        }

        //int donnetest[] ={1,200};
       // int donnetest[] ={9};
        //sendspichar('f');
        //forge(2,'l',&donnetest,&trametx_SPI);//forgage de la trame spi à transmettre
      // forge(1,'s',&donnetest,&trametx_SPI);//forgage de la trame spi à transmettre
      // send_SPI(&trametx_SPI);//envoi de la trame spi


      /**  sendspichar('f');
        __delay_cycles(100);
       sendspichar('1');
        __delay_cycles(100);
       sendspichar('\0');
       delay(1000);**/


//////////////////////pas testé ni fini
       if(mode==1){//mode auto
           deplacementautonome();//lance les fonctions de detections d obstables

       }else{
           //rien attente des ordres venant de luart
       }
        //////////////////////
    }
}


/*
 * 0101010001100101011000010110110100100000010100110100101101000110
 */


