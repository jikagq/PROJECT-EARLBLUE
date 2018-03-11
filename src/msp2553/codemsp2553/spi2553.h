/*
 * spi2553.h
 *
 *  Created on: 8 mars 2018
 *      Author: theo-
 */

#ifndef SPI2553_H_
#define SPI2553_H_

#define TAILLETRAMESPI 16 //taille de la trame
#define TAILLEVALSPI 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEURSPI 4 //nombre de valueur à transmettre

extern volatile char received_ch;
extern volatile char trametx_SPI[TAILLETRAMESPI];

void Init_SPI (void);
void send_SPI (char* trame_SPI);
void sendspichar(char c);
void raztramespi(void);

#endif /* SPI2553_H_ */
