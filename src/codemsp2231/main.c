/**
 * main.c
 */

#include <msp430.h> 

#include "main.h"
#include "util.h"
#include "pwmservo.h"
#include "spi2231.h"

int freq=500;
int etat=1;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;
	initSPI();
	//_BIS_SR( GIE);             // Enter LPM0 w/ interrupt
	do{
	    if(etat==1){
	       P1OUT |= 0x01;
	       delay(freq);
	       P1OUT &= ~0x01;
	       delay(freq);
	    }
	}while(1);

	return 0;
}
