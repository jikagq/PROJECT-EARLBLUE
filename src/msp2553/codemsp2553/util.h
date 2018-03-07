/*
 * util.h
 *
 *  Created on: 3 mars 2018
 *      Author: theo-
 */

#include <msp430g2553.h>
#include <msp430.h>

#ifndef UTIL_H_
#define UTIL_H_

#define TAILLETRAME 16 //taille de la trame
#define TAILLEVAL 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEUR 4 //nombre de valueur a transmettre

void delay (unsigned int ms);
void itoad(long unsigned int value, char *result, int base);
void raztrame(char *trame);
int forge(int nbvaleur,char type, int *dataint, char *trameaenvoyer);
int slot(int slotnumber);
int substringsemicolon(int debut,int fin);



#endif /* UTIL_H_ */
