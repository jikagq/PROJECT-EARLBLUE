//------------------------------------------------------------------------------
/*
 * spi2553.c
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
#include "drivermoteur.h"
#include "scan.h"
#include "ADC.h"
#include "capteurInfrarouge.h"

volatile char received_ch = 0;//buffer
volatile char trametx_SPI[TAILLETRAMESPI];//trame spi à envoyer



void Init_SPI (void)
{

	  P1DIR |= BIT4;//bit 5 sortie
	  P1OUT |= BIT4;//spi slave cs=1


	  P1SEL |= (BIT6 | BIT7 | BIT5);
	  P1SEL2 |= (BIT6 | BIT7 | BIT5);

	  UCB0CTL1 |= UCSWRST;

	  UCB0CTL0 |= (UCCKPH | UCMSB | UCMST | UCSYNC | UCCKPL);  // 3-pin, 8-bit SPI master//ajout de ucckpl !?
	  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	  // Bit clk prescaler setting
	  UCB0BR0 |= 0x02;                          // /2
	  UCB0BR1 = 0;                              //
	  // Modulation Control Register
	  UCA0MCTL = 0;                             // No modulation
	  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	  P1OUT &= ~BIT4;//selection de l'esclave cs low
	  P1OUT |= BIT4; // reset slave cs high

	  __delay_cycles(75);
}
/*
 * manque la reception qui se trouve quelque part sur mon autre pc
 */
void send_SPI (char* trame_SPI)//envoi du tableau
{
    int i=0;

    while(trame_SPI[i] != '\0'){//lecture du tab jusqu'a la fin de trame
        sendspichar(trame_SPI[i]);
        i++;
        __delay_cycles(75);//attente entre 2 transmissions
    }
    i++;
    sendspichar(trame_SPI[i]);//dernier char

   // raztramespi();
}

void sendspichar(char c){//envoi d'1 seul char
    P1OUT &= ~BIT4;//selection de l'esclave cs low
    while ((UCB0STAT & UCBUSY));   // attend que USCI_SPI soit dispo.
    while (!(IFG2 & UCB0TXIFG));
    UCB0TXBUF = c;
    __delay_cycles(20);
    P1OUT |= BIT4; // reset slave cs high
}




void raztramespi(void){//raz de la trame uart
    int index=0;
    for(index=0;index<TAILLETRAMESPI;index++){//ini de la trame rx
        trametx_SPI[index]=' ';
    }
    //indexrxbufferuart=0;//mettre le raz du rx spi
}




















/**int forgespi(int nbvaleur,char type, int *dataint, char *trametx){//permet de creer une trame a envoyer en spi
    int i=0;
    int cpt=0;
    int compteurtrame=4;
    char s[6];
    int flag_overflow=0;//donnée utile a transmettre plus grand que la taille max autorisé par une seule trame

    trametx[0]='f';//1er caractere
    trametx[1]='2';
    trametx[2]=type;
    trametx[3]=';';
    int a=dataint[i];

    for(i=0;i<nbvaleur;i++){
        itoad(dataint[i], &s, 10);//conversion int en char*
        while(s[cpt] != '\0'){
            trametx[compteurtrame]=s[cpt];
            cpt++;//compteur de la valeur en cours
            compteurtrame++;//compteyr du curseur dans la trame
        }
        cpt=0;
        if(i<nbvaleur-1){//bloquer le dernier ';'
            trametx[compteurtrame]=';';
            compteurtrame++;
        }
    }
    if(compteurtrame-2 >= TAILLETRAMESPI -2 ){//-1 a cause de l'offset trametx[] et -2 car c'est la taille d'une trame -l le 1er carac -1 le dernier carac
        flag_overflow=1;
    }else{
        trametx[TAILLETRAMESPI-1]='\0';//fin de trame
        for(i=0;i<TAILLETRAMESPI;i++){//relecture afficage
            //transmit(trametx[i]);
            if(trametx[i]=='\0'){
               //printf("ok");
            }
        }
    }
   //raztrame();
return flag_overflow;
}**/
