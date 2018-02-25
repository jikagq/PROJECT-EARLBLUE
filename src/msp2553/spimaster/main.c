#include <msp430.h>

volatile char received_ch = 0;

void delay (unsigned int ms)
{
    volatile unsigned int i, z;
    i=100;
    while (i--) {
        z=ms;
        while(z--);
    }
}

int main(void)
{
    int i=0;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  if (CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
  {
      __bis_SR_register(LPM4_bits);
  }
  else
  {
      //Factory set
      BCSCTL1 = CALBC1_1MHZ;
      DCOCTL = CALDCO_1MHZ;
  }

  P1DIR |= BIT4;//bit 5 sortie
  P1OUT |= BIT4;//spi slave cs=1


  P1SEL |= (BIT6 | BIT7 | BIT5);
  P1SEL2 |= (BIT6 | BIT7 | BIT5);

  UCB0CTL1 |= UCSWRST;

  UCB0CTL0 |= (UCCKPH | UCMSB | UCMST | UCSYNC | UCCKPL);  // 3-pin, 8-bit SPI master//ajout de ucckpl !?
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  // Bit clk prescaler setting
  UCB0BR0 |= 0x02;                          // /2
  UCB0BR1 = 0;                              //
  // Modulation Control Register
  UCA0MCTL = 0;                             // No modulation
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**



// Ajout d'une boucle infinie afin d'envoyer en boucle un caractère
  do{
    P1OUT &= ~BIT4;//selection de l'esclave cs low
    while (!(IFG2 & UCB0TXIFG)); // Buffer ready
    if(i==0){
        UCB0TXBUF = 'a'; // Envoie de caractère. Changement de valeur pour envoie d'un nouveau caractère.
        i=1;
    }else{
        UCB0TXBUF = 'b';
        i=0;
    }




      while (!(IFG2 & UCB0RXIFG));
      received_ch = UCB0RXBUF;
    P1OUT |= BIT4;                            // reset slave cs high
    delay(1000);
  }while (1);
}
