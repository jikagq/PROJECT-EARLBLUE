/*
 * util.c
 *
 *  Created on: 3 mars 2018
 *      Author: theo-
 */

#include <msp430g2231.h>
#include <msp430.h>

#include "main.h"
#include "util.h"
#include "pwmservo.h"
#include "spi2231.h"



void raztrame(char *trame){//raz trame uart ou spi
    int index=0;
     for(index=0;index<TAILLETRAME;index++){//ini de la trame rx
         trame[index]=" ";
     }
}

int forge(int nbvaleur,char type, int *dataint, char *trameaenvoyer){//permet de creer une trame a envoyer en spi ou uart
    int i=0;
    int cpt=0;
    int compteurtrame=4;
    char s[TAILLEVAL];
    int flag_overflow=0;//donnée utile a transmettre plus grand que la taille max autorisé par une seule trame


    trameaenvoyer[0]='f';//trame forge
    trameaenvoyer[1]='2';//je sais pas encore
    trameaenvoyer[2]=type;//indique a quoi sert la trame
    trameaenvoyer[3]=';';//1er ; donnée utile apres


    for(i=0;i<nbvaleur;i++){
        itoad(dataint[i], &s, 10);//conversion int en char*
        while(s[cpt] != '\0'){
            trameaenvoyer[compteurtrame]=s[cpt];
            cpt++;//compteur de la valeur en cours
            compteurtrame++;//compteyr du curseur dans la trame
        }
        cpt=0;
        if(i<nbvaleur-1){//bloquer le dernier ';'
            trameaenvoyer[compteurtrame]=';';
            compteurtrame++;
        }
    }
    if(compteurtrame-2 >= TAILLETRAME -2 ){//-1 a cause de l'offset trametx[] et -2 car c'est la taille d'une trame -l le 1er carac -1 le dernier carac
        flag_overflow=1;//a implémenter
    }else{
        trameaenvoyer[compteurtrame]='\0';//fin de trame
    }

return flag_overflow;
}

int slot(int slotnumber, char *trameadecoder){//decodage de la trame forge
    int i;
    int var=0;
    int cptseparateur=0;
    int pos=0;//0:gauche 1:droite
    int debut=0;
    int fin=0;
    char *p=trameadecoder;

    for(i=3;i<TAILLETRAME-1;i++){//fin de l'entete forge Ã  3
        if((trameadecoder[i]==';') || (trameadecoder[i]=='\0')){//;gauche
            if(pos==0){
               pos=1;
               debut=i;
               cptseparateur++;
            }else{//;droit
               pos=0;
               fin=i;
               if(cptseparateur == slotnumber){
                //coupe
                   var=substringsemicolon(debut, fin, p);
                   i=TAILLETRAME-1;//quite la boucle dÃ¨s que la veleur est extraites pour pas se taper toutes la trame
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

int substringsemicolon(int debut,int fin, char *trame ){//conversion d'une donnée de la trame uart char*->int
    char subsstr[TAILLEVAL];
    int a=0;
    int b=0;
    int var=-1;


    b=debut;
    while(b<fin){
        subsstr[a]=trame[b+1];
        b++;
        a++;
    }
    var = atoi(subsstr);
    return var;
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

