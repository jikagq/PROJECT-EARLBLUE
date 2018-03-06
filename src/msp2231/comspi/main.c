/*msp2132 spi reception*/
#include <msp430.h>

#define SPITAILLETRAME 16 //taille de la trame
#define SPITAILLEVAL 6 //val max+1 nombre de slot d'un entier
#define SPINOMBREDEVALEUR 4 //nombre de valueur a transmettre

volatile unsigned int i;
volatile int unsigned spirxbuffer=0;
volatile char spirxtrame[SPITAILLETRAME];

int freq=0;
int etat=0;

void delay (unsigned int ms)
{
    volatile unsigned int i, z;
    i=100;
    while (i--) {
        z=ms;
        while(z--);
    }
}

void anvilspi(){//gestion des trames forge
    char action;

    action=spirxtrame[2];
    switch(action){
          case 'l':{
                ledparam();
                raztrame();
                break;
                }
          default :{
                raztrame();
                break;
                }
          }
    raztrame();
}

void ledparam(void){

    etat = slot(1);
    freq = slot(2);

}

int slot(int slotnumber){
    int i;
    int var=0;
    int cptseparateur=0;
    int pos=0;//0:gauche 1:droite
    int debut=0;
    int fin=0;

    for(i=3;i<SPITAILLETRAME-1;i++){//fin de l'entete forge à 3
        if((spirxtrame[i]==';') || (spirxtrame[i]=='\0')){//;gauche
            if(pos==0){
               pos=1;
               debut=i;
               cptseparateur++;
            }else{//;droit
               pos=0;
               fin=i;
               if(cptseparateur == slotnumber){
                //coupe
                   var=substringsemicolon(debut, fin);
                   i=SPITAILLETRAME-1;//quite la boucle dès que la veleur est extraites pour pas se taper toutes la trame
               }else{
                   pos=1;
                   debut=i;
                   cptseparateur++;
               }
            }
        }
    }
   return var;
}

int substringsemicolon(int debut,int fin){
    char subsstr[6];
    int a=0;
    int b=0;
    int var=-1;


    b=debut;
    while(b<fin){
        subsstr[a]=spirxtrame[b+1];
        b++;
        a++;
    }
    var = atoi(subsstr);
    return var;
}

void raztrame(){
    for(spirxbuffer=0;spirxbuffer<SPITAILLETRAME;spirxbuffer++){//ini de la trame rx
        spirxtrame[spirxbuffer]=" ";
    }
    spirxbuffer=0;
}

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


  if(etat==1){
      P1OUT |= 0x01;
      delay(freq);
      P1OUT &= ~0x01;
      delay(freq);
  }

}

// USI interrupt service routine
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
   /** if ('a' == USISRL)
       P1OUT |= 0x01;
     else
       P1OUT &= ~0x01;
    **/

    unsigned char c;
    c = USISRL;
        if(c == '\0'){//fin de la trame
            spirxtrame[spirxbuffer]=c;
            anvilspi();
        }else{//sinon on ajoute le caractaire à la chaine
           spirxtrame[spirxbuffer]=c;
           spirxbuffer++;
        }
     USISRL = P1IN;
     USICNT = 8;
}
