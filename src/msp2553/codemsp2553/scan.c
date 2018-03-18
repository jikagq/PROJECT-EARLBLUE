/*
 * scan.c
 *
 *  Created on: 15 mars 2018
 *      Author: theo-
 */


#include "main.h"
#include "util.h"
#include "uart.h"
#include "spi2553.h"
#include "drivermoteur.h"
#include "scan.h"
#include "ADC.h"
#include "capteurInfrarouge.h"

/*        0:0
         * 1:22.5
         * 2:45
         * 3:67.5
         * 4:90
         * 5:112.5
         * 6:135
         * 7:157.5
         * 8:180
         */
///////////pas testé

void iniservo(void){
    positionservo(4);//position 90°
    delay(1000);//attente position du servo
}

int scanner(void){//scan de la distance la plus grande
    int distance=0;
    int tabdistance[9]={0,0,0,0,0,0,0,0,0};
    int sauvgardeposition=0;
    int i=0;

    positionservo(0);//position 0°
    delay(5000);//attente position du servo

    for(i=0;i<9;i++){
        positionservo(i);
        delay(500);
        tabdistance[i]=aquisition();
        delay(500);
    }
    positionservo(4);

    distance=tabdistance[i];

    for(i=0;i<9;i++){
        if(tabdistance[i]<distance){
            distance=tabdistance[i];
            sauvgardeposition=i;
        }
    }

    return sauvgardeposition;//+1 pour que ça colle avec le switch case
}

int positionservo(int pos){
    int ok;
    //int tab[0]=pos;
    int tab[] ={pos};//????????????????
    forge(1,'s',&tab,&trametx_SPI);//forgage de la trame spi à transmettre
    send_SPI(&trametx_SPI);//envoi de la trame spi
    //receive spi attente ack

    return ok;
}
//////////////////


void deplacementautonome(void){
           int rotation=0;
           avancer();
           if(obstacle() == 1){//obstacle ? appel fonction detection obstavle renvoi 1 si y en a un
                    stop();
                    rotation = scanner();//scan de l env
                    switch(rotation){//valeurs à modifier
                    case 0:{
                        gaucheauto(13);
                        break;
                           }

                    case 1:{
                        gaucheauto(13);
                        break;
                           }
                    case 2:{
                        gaucheauto(13);
                        break;
                         }

                     case 3:{
                         gaucheauto(13);
                         break;
                         }
                     case 4:{
                         avancer();//?????????
                         break;
                         }

                     case 5:{
                         droiteauto(13);
                         break;
                         }

                     case 6:{
                         droiteauto(13);
                         break;
                         }

                     case 7:{
                         droiteauto(13);
                         break;
                         }
                     case 8:{
                         droiteauto(13);
                         break;
                         }
                     default :{
                         stop();
                         break;
                         }
                     }
                //avancer();

            }else{
                avancer();
            }
}
