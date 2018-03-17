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

/*     1:0
         * 2:22.5
         * 3:45
         * 4:67.5
         * 5:90
         * 6:112.5
         * 7:135
         * 8:157.5
         * 9:180
         */
///////////pas testé
int scanner(void){//scan de la distance la plus grande
    int distance;
    int distancemax;
    int sauvgardeposition=0;

    int position=0;

    int i=0;

    positionservo(1);//position 0°
    delay(5000);

    for(i=1;i<10;i++){

        positionservo(i);
        delay(1000);
        distance=aquisition();
        if(distancemax > distance){//tableaudistance[]=aquisition
            distancemax=distance;
            sauvgardeposition=i;
        }

    }
    positionservo(5);

    return sauvgardeposition;
}

int positionservo(int pos){
    int ok;
    int tab[0]=pos;

    forge(1,'s',&tab,&trametx_SPI);//forgage de la trame spi à transmettre
    send_SPI(&trametx_SPI);//envoi de la trame spi
    //receive spi attente ack

    return ok;
}
//////////////////
