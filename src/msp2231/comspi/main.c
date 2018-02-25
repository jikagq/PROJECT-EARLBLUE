#include <msp430.h>


int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  P1OUT =  0x10;                        // P1.4 set, else reset
  P1REN |= 0x10;                        // P1.4 pullup

  P1DIR = 0x01 ;                         // P1.0 output, else input



  USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIOE; // Port, SPI slave p406
  //USIPE7 sdi 1
  //USIPE6 sdo 1
  //USIPE5 clk 1
  //USIOE Data output enable 1
  USICTL1 |= USIIE;                     // Counter interrupt, flag remains set p407
  USICTL0 &= ~USISWRST;                 // USI released for operation p406
  USISRL = P1IN;                        // init-load data p409
  USICNT = 8;                           // init-load counter nb de bit p408

  _BIS_SR(LPM0_bits + GIE);             // Enter LPM0 w/ interrupt
}

// USI interrupt service routine
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
    if ('a' == USISRL)
       P1OUT |= 0x01;
     else
       P1OUT &= ~0x01;
     USISRL = P1IN;
     USICNT = 8;
}
