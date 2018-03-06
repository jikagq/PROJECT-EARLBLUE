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


volatile char received_ch = 0;

void delay (unsigned int ms)
{
    volatile unsigned int i, z;
    i=100;
    while (i--) {
        z=ms;
        while(z--);
    }
}

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

int send_SPI (char* trame_SPI)
{
  int i=0;
// Ajout d'une boucle infinie afin d'envoyer en boucle un caractère
  do{
    P1OUT &= ~BIT4;//selection de l'esclave cs low
    while (!(IFG2 & UCB0TXIFG)); // Buffer ready
    {
        UCB0TXBUF = trame_SPI [i]; // Envoie de caractère. Changement de valeur pour envoie d'un nouveau caractère.
        i++;
    }
 
    while (!(IFG2 & UCB0RXIFG));
    received_ch = UCB0RXBUF;
    P1OUT |= BIT4;                            // reset slave cs high
  }while (trame_SPI [i] =! '\0');             // Trame_SPI  n'est pas nul
}

