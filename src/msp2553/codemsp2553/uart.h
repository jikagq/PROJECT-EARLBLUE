/*
 * uart.h
 *
 *  Created on: 3 mars 2018
 *      Author: theo-
 */

#include <msp430g2553.h>
#include <msp430.h>

#ifndef UART_H_
#define UART_H_

#define TAILLETRAMEUART 16 //taille de la trame
#define TAILLEVALUART 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEURUART 4 //nombre de valueur a transmettre

extern volatile int unsigned indexrxbufferuart;
extern volatile char rxtrameuart[TAILLETRAMEUART];


//extern int slotuart(int slotnumber);
//extern int substringsemicolonuart(int debut,int fin);
extern void interpreteuruart(void);
extern void anviluart(void);
extern void raztrameuart(void);
extern void InitUART(void);
extern void TXdata( unsigned char c );
extern void pong(void);
extern void ack(void);
extern void nak(void);
extern void debug(char *texte, int valeur);

#endif /* UART_H_ */
