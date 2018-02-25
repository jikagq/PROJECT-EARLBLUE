//------------------------------------------------------------------------------
// uart_simple.c
//
// test de l'UART : ?cho des caract?res re?us
//
//                              benoit.decoux@esigelec.fr - 28/01/2013
//------------------------------------------------------------------------------
#include <msp430g2553.h>
#include <msp430.h>

#define TAILLETRAME 16 //taille de la trame
#define TAILLEVAL 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEUR 4 //nombre de valueur a transmettre

volatile unsigned int i;
volatile int unsigned rxbuffer=0;
volatile char rxtrame[TAILLETRAME];
int onoffled1=0;
int tpsh=1000;
int tpsb=500;
int compteurtrameinutile=0;

//int val=0;
//char str[] = "1000";


void InitUART(void)
{
    P1SEL |= (BIT1 | BIT2);                     // P1.1 = RXD, P1.2=TXD
        P1SEL2 |= (BIT1 | BIT2);                    // P1.1 = RXD, P1.2=TXD
        UCA0CTL1 = UCSWRST;                         // SOFTWARE RESET
        UCA0CTL1 |= UCSSEL_3;                       // SMCLK (2 - 3)

        UCA0CTL0 &= ~(UCPEN | UCMSB | UCDORM);
        UCA0CTL0 &= ~(UC7BIT | UCSPB | UCMODE_3 | UCSYNC); // dta:8 stop:1 usci_mode3uartmode
        UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**

        UCA0BR0 = 104;                              // 1MHz, OSC16, 9600 (8Mhz : 52) : 8/115k
        UCA0BR1 = 0;                                // 1MHz, OSC16, 9600
        UCA0MCTL = 10;

        /* Enable USCI_A0 RX interrupt */
        IE2 |= UCA0RXIE;
}

void TXdata( unsigned char c )
{
    P1OUT ^= BIT6;//debug
    while (!(IFG2&UCA0TXIFG));  // USCI_A0 TX buffer ready?
    UCA0TXBUF = c;              // TX -> RXed character
}

void delay (unsigned int ms)
{
    volatile unsigned int i, z;
    i=100;
    while (i--) {
        z=ms;
        while(z--);
    }
}

void interpreteur(){
   char rxcar;
   rxcar=rxtrame[0];//recup du 1er carac reprsentant l'opération

   switch(rxcar){
      case 'c':{//ping
            pong();
            raztrame();
            break;
            }
      case 'L':{
            led1();
            raztrame();
            break;
            }
      case 't':{
            parser();
            raztrame();
            break;
            }
      default :{
            nak();
            raztrame();
            break;
            }
      }
}

void parser(){
    int i;
    for(i=1;i<TAILLETRAME-1;i++){//à completer quand y aura besoin
        if(rxtrame[i]==';'){
            //val = atoi(str);convertir les char* en int
        }
    }
    ack();
    raztrame();
}

void led1(){
   if(rxtrame[1]=='1'){
       ack();
       onoffled1=1;
   }
   if(rxtrame[1]=='0'){
       ack();
       onoffled1=0;
   }
   if((rxtrame[1] != '1') && (rxtrame[1] != '0')){
        nak();
   }
   raztrame();

}

void pong(){
    unsigned int i;
    char pong[] = "pong";
    for(i=0;i<5;i++){
        TXdata(pong[i]);
    }

}

void ack(){
    unsigned int i;
    char ack[] = "ack";
    for(i=0;i<4;i++){
        TXdata(ack[i]);
    }
}
void nak(){
    unsigned int i;
    char nak[] = "nak";
    for(i=0;i<4;i++){
        TXdata(nak[i]);
    }
}

void raztrame(){
    for(rxbuffer=0;rxbuffer<16;rxbuffer++){//ini de la trame rx
        rxtrame[rxbuffer]=" ";
    }
    rxbuffer=0;
}

void itoad(long unsigned int value, char *result, int base){//conversion entier en char *
      // check that the base if valid
      if (base < 2 || base > 36){
          *result = '\0';
      }

      char *ptr = result, *ptr1 = result, tmp_char;
      int tmp_value;

      do{
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
      }while(value);

      // Apply negative sign
      if (tmp_value < 0) *ptr++ = '-';
      *ptr-- = '\0';
      while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
      }

}
void debug(char *texte, int valeur){
    int i;
    char intenchar[5];

    while(texte[i] != '\0'){
        TXdata(texte[i]);
    }
    TXdata(' ');
    itoad(valeur, &intenchar, 10);

    TXdata('\0');//fin
}


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT


    if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
    {
        __bis_SR_register(LPM4_bits); // Low Power Mode #trap on Error
    }
    else
    {
        // Factory parameters
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = CALDCO_1MHZ;
    }


    InitUART();

    __bis_SR_register(GIE); // interrupts enabled

    P1DIR |= BIT0;                  // configure P1.0 as output
    P1DIR |= BIT6;

    P1OUT &= ~BIT0;                  // configure P1.0 as output
    P1OUT &= ~BIT6;

    raztrame();
    rxbuffer=0;

    while(1){

        if(onoffled1 == 1){
            //char chainedebug[] = "ici";//texte de debug
            //debug(&chainedebug,46);//données à debug en uart
            P1OUT |= BIT0;
            delay(tpsh);
            P1OUT &= ~BIT0;
            delay(tpsb);
        }else{
           P1OUT &= ~BIT0;
        }


       /** if(val == 1000){
            P1OUT |= BIT0;
            TXdata('c');
            delay(tpsh);
            P1OUT &= ~BIT0;
            delay(tpsb);
        }**/
        //TXdata('c');

    }
    return 0;
}




#pragma vector=USCIAB0RX_VECTOR//reception d'une trame
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c;
    c = UCA0RXBUF;

    P1OUT ^= BIT6;//debug


   /** if(rxbuffer==TAILLETRAME){//secu pour pas dépasser la taille max de la trame
        rxbuffer=0;
   }**/

    if(c == '\0'){//fin de la trame
        rxtrame[rxbuffer]=c;
        //TXdata('c');
        //TXdata(rxtrame[0]);//renvoie le 1er carac pour debug
        interpreteur();
    }else{//sinon on ajoute le caractaire à la chaine
       rxtrame[rxbuffer]=c;
       rxbuffer++;
    }

}



