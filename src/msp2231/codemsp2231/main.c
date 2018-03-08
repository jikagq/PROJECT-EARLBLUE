/**
 * main.c
 */

#include <msp430.h> 

#include "main.h"
#include "util.h"
#include "pwmservo.h"
#include "spi2231.h"

int freq=0;
int etat=0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	initSPI();
	 if(etat==1){
	      P1OUT |= 0x01;
	      delay(freq);
	      P1OUT &= ~0x01;
	      delay(freq);
	  }
	return 0;
}
