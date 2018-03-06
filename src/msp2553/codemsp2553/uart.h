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

void InitUART(void);
void TXdata( unsigned char c );
void pong(void);
void ack(void);
void nak(void);
void debug(char *texte, int valeur);

#endif /* UART_H_ */
