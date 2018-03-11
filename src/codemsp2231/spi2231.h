/*
 * spi2231.h
 *
 *  Created on: 8 mars 2018
 *      Author: theo-
 */


#ifndef SPI2231_H_
#define SPI2231_H_

#define TAILLETRAMESPI 16 //taille de la trame
#define TAILLEVALSPI 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEURSPI 4 //nombre de valueur a transmettre

extern volatile int unsigned spirxbuffer;
extern volatile char spirxtrame[TAILLETRAMESPI];
extern int freq;
extern int etat;

void anvilspi(void);
void ledparam(void);
void SendSpislave(char c);
void SendSpitrameslave(char *data);

#endif /* SPI2231_H_ */
