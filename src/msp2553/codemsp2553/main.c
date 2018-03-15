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
#include "drivermoteur.h"
#include "scan.h"

volatile unsigned int i;

int onoffled1=0;
int freq=1000;

int mode=0;

void ledspi(void)// led 2231 par spi
{
    int dataint[NOMBREDEVALEURSPI];
    //!!!utilisation des fonction generique dans util.c

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
    int rotation;

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
    Init_SPI();//!attention bug avec le spi!
    //testmoteur();
    initmoteur();
    //avancer();
    //delay(1000);
    //stop();//ici on detrect l'obstavcle
    //gaucheauto(50);//on tourne pour esquiver
    //droiteauto(50);


    //int donnetest[] ={1,200};


    __bis_SR_register(GIE); // interrupts enabled

    P1DIR |= BIT0;                  // configure P1.0 as output
    P1OUT &= ~BIT0;                  // configure P1.0 as output


    while(1){
        if(onoffled1 == 1){
            P1OUT |= BIT0;
            delay(freq);
            P1OUT &= ~BIT0;
            delay(freq);
        }else{
           P1OUT &= ~BIT0;
        }

        //forge(2,'l',&donnetest,&trametx_SPI);//forgage de la trame spi à transmettre
        //send_SPI(&trametx_SPI);//envoi de la trame spi
        //delay(1000);
        //sendspichar('f');
        //__delay_cycles(75);
        //sendspichar('1');
        //__delay_cycles(75);
        //sendspichar('\0');

        if(mode==1){
        //lance les fonctions de detections dobstables
            avance();
            //if(obstacle == 1)obstacle ? appel fonction detection obstavle renvoi 1 si y en a un
            {
                stop();
                rotation = scanner();

                switch(rotation){
                case 1:{
                    gaucheauto(50);
                    break;
                       }

                case 2:{
                    gaucheauto(50);
                    break;
                       }
                case 3:{
                    gaucheauto(50);
                    break;
                     }

                 case 4:{
                     gaucheauto(50);
                     break;
                     }
                 case 5:{
                     avancer();
                     break;
                     }

                 case 6:{
                     droiteauto(50);
                     break;
                     }

                 case 7:{
                     droiteauto(50);
                     break;
                     }

                 case 8:{
                     droiteauto(50);
                     break;
                     }
                 case 9:{
                     droiteauto(50);
                     break;
                     }
                 default :{
                     stop();
                     break;
                     }
                }
                avancer();
            }
        }else{
            avancer();
        }
    }
}





