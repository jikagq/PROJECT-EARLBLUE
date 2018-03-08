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

//ajouer les variables globales

volatile char received_ch = 0;


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
}

void send_SPI (char* trame_SPI)
{
  int i=0;
// Ajout d'une boucle infinie afin d'envoyer en boucle un caractÃ¨re
  do{
    P1OUT &= ~BIT4;//selection de l'esclave cs low
    while (!(IFG2 & UCB0TXIFG)); // Buffer ready
    {
        UCB0TXBUF = trame_SPI [i]; // Envoie de caractÃ¨re. Changement de valeur pour envoie d'un nouveau caractÃ¨re.
        i++;
    }
 
    while (!(IFG2 & UCB0RXIFG));
        received_ch = UCB0RXBUF;
    P1OUT |= BIT4;                            // reset slave cs high
  }while (trame_SPI [i] =! '\0');             // Trame_SPI  n'est pas nul what ?
}

