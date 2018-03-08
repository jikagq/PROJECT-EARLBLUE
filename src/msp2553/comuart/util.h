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

void delay (unsigned int ms);
void itoad(long unsigned int value, char *result, int base);
void forge(int nbvaleur, char type, int *dataint, char *trametx);



#endif /* UTIL_H_ */
