/*
 * uart.c
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

void InitUART(void)
{
    P1SEL |= (BIT1 | BIT2);                     // P1.1 = RXD, P1.2=TXD
        P1SEL2 |= (BIT1 | BIT2);                    // P1.1 = RXD, P1.2=TXD
        UCA0CTL1 = UCSWRST;                         // SOFTWARE RESET
        UCA0CTL1 |= UCSSEL_3;                       // SMCLK (2 - 3)

        UCA0CTL0 &= ~(UCPEN | UCMSB | UCDORM);
        UCA0CTL0 &= ~(UC7BIT | UCSPB | UCMODE_3 | UCSYNC); // dta:8 stop:1 usci_mode3uartmode
        UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**

        UCA0BR0 = 104;                              // 1MHz, OSC16, 9600 (8Mhz : 52) : 8/115k
        UCA0BR1 = 0;                                // 1MHz, OSC16, 9600
        UCA0MCTL = 10;

        /* Enable USCI_A0 RX interrupt */
        IE2 |= UCA0RXIE;
}

void TXdata( unsigned char c )
{
    P1OUT ^= BIT6;//debug
    while (!(IFG2&UCA0TXIFG));  // USCI_A0 TX buffer ready?
    UCA0TXBUF = c;              // TX -> RXed character
}

void pong(void){
    unsigned int i;
    char pong[] = "pong";
    for(i=0;i<5;i++){
        TXdata(pong[i]);
    }

}

void ack(void){
    unsigned int i;
    char ack[] = "ack";
    for(i=0;i<4;i++){
        TXdata(ack[i]);
    }
}
void nak(void){
    unsigned int i;
    char nak[] = "nak";
    for(i=0;i<4;i++){
        TXdata(nak[i]);
    }
}

void debug(char *texte, int valeur){
    int i;
    char intenchar[5];

    while(texte[i] != '\0'){
        TXdata(texte[i]);
    }
    TXdata(' ');
    itoad(valeur, &intenchar, 10);

    TXdata('\0');//fin
}
