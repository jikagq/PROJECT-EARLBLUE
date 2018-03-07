/*
 * spi2553.h
 *
 *  Created on: 3 mars 2018
 *      Author: theo-
 */

#include <msp430g2553.h>
#include <msp430.h>

#ifndef SPI2553_H_
#define SPI2553_H_

#define TAILLETRAMESPI 16 //taille de la trame
#define TAILLEVALSPI 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEURSPI 4 //nombre de valueur a transmettre

int forgespi(int nbvaleur,char type, int *dataint, char *trametx);
void Init_SPI (void);


#endif /* SPI2553_H_ */

