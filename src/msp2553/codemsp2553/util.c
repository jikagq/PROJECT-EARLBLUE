/*
 * util.c
 *
 *  Created on: 3 mars 2018
 *      Author: theo-
 */

#include <msp430g2553.h>
#include <msp430.h>

#include "main.h"
#include "util.h"
#include "uart.h"
#include "spi2553.h"

void delay (unsigned int ms)
{
    volatile unsigned int i, z;
    i=100;
    while (i--) {
        z=ms;
        while(z--);
    }
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

void forge(int nbvaleur,char type, int *dataint, char *trametx){//forge à utilisé plus tard avec concatenationdata
    int i=0;
    int cpt=0;
    int compteurtrame=4;
    char s[6];
    int flag_overflow=0;//donnée utile a transmettre plus grand que la taille max autorisé par une seule trame

    trametx[0]='f';//1er caractere
    trametx[1]='2';
    trametx[2]=type;
    trametx[3]=';';
    //data<=TAILLETRAME-2//taille max des données utile
    int a=dataint[i];

    for(i=0;i<nbvaleur;i++){
        itoad(dataint[i], &s, 10);//conversion int en char*
        while(s[cpt] != '\0'){
            //printf("%c",s[cpt]);
            trametx[compteurtrame]=s[cpt];
            cpt++;//compteur de la valeur en cours
            compteurtrame++;//compteyr du curseur dans la trame
        }
        cpt=0;
        //printf("\n");
        if(i<nbvaleur-1){//bloquer le dernier ';'
            trametx[compteurtrame]=';';
            compteurtrame++;
        }
    }
    //printf(" compteur:%d \n ",compteurtrame);
    if(compteurtrame-2 >= 16 -2 ){//-1 a cause de l'offset trametx[] et -2 car c'est la taille d'une trame -l le 1er carac -1 le dernier carac
    //printf("overflow\n");
    flag_overflow=1;
    }else{
        trametx[16-1]='\0';//fin de trame
        //printf("-> ");
        for(i=0;i<16;i++){//relecture afficage
            //printf("%c",trametx[i]);
            //transmit(trametx[i]);
            if(trametx[i]=='\0'){
               //printf("ok");
            }
        }
    }
   // raztrame();
    //receive();
return flag_overflow;
}
