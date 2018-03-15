/*
 * code principal msp2231
 *
 *
 *
 *
 */

#include <msp430.h> 

#include "main.h"
#include "util.h"
#include "pwmservo.h"
#include "spi2231.h"

int freq=500;//led 2231
int etat=1;//si la led doit cli

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;
	initSPI();
	initpwmservo();

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

/*
 * 0101010001100101011000010110110100100000010100110100101101000110
 */
