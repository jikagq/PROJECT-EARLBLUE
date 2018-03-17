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


void iniboard(void){
    P1DIR = 0x00; // IN high z
    P2DIR = 0x00; // IN
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
}

int main(void)
{
    iniboard();



	P1DIR |= BIT0;//led

	initSPI();
	initpwmservo();

	/**int i=0;
	for(i=1;i<10;i++){
	    position(i);
	    delay(5000);
	}**/





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
