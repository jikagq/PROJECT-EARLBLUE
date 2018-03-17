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


////////////pose pb
void raztrame(char *trame){//raz trame uart ou spi
    int index=0;
     for(index=0;index<TAILLETRAME;index++){//ini de la trame rx
         trame[index]='\0';
     }
}
////////////

/*
 * cr�ation d'une trame "standard" spi/uart
 * je crois que �a marche pas avec les char ?
 */
int forge(int nbvaleur,char type, int *dataint, char *trameaenvoyer){//nb de valeur � envoyer;type/action de la trame;tableau d'entier � transm�ttre;tableau spi � envoyer
    int i=0;//indique le nombre de fois que l'ont doit mettre un entier dans la chaine � envoyer
    int cpt=0;//nombre de char correspondant au nombre de digits d'un nombre
    int compteurtrame=4;//curseur du tableau � envoyer en spi =4 car les donn�es utile dans la trame commence ici
    char s[TAILLEVAL];//chaine contenant l'entier convertie en *char
    int flag_overflow=0;//donn�e utile � transmettre plus grand que la taille max autoris� par une seule trame (pas impl�ment�)

    //ent�te
    trameaenvoyer[0]='f';//trame forge
    trameaenvoyer[1]='2';//je sais pas encore
    trameaenvoyer[2]=type;//indique � quoi sert la trame
    trameaenvoyer[3]=';';//1er ';' les donn�es utile sont apres


    for(i=0;i<nbvaleur;i++){//parcours le tableau d'entier en entr�e
        itoad(dataint[i], &s, 10);//conversion int en char*
        while(s[cpt] != '\0'){//tant que la chaine n'est pas finie
            trameaenvoyer[compteurtrame]=s[cpt];//ajout de l entier converti dans la chaine � transm�tre
            cpt++;//compteur de la valeur en cours indique le digit � ajouter
            compteurtrame++;//compteyr du curseur dans la trame � envoyer
        }
        cpt=0;//le 1er nb � �t� ajouter donc raz
        if(i<nbvaleur-1){//bloquer le dernier ';'
            trameaenvoyer[compteurtrame]=';';
            compteurtrame++;
        }
    }
    if(compteurtrame-2 >= TAILLETRAME -2 ){//-1 a cause de l'offset trametx[] et -2 car c'est la taille d'une trame -l le 1er carac -1 le dernier carac
        flag_overflow=1;//a impl�menter
    }else{
        trameaenvoyer[compteurtrame]='\0';//fin de trame
    }
//ajouter un crc � la fin
return flag_overflow;// pas encore utilis�
}

/*
 * d�codage des nombres contenu dans une trame forge
 *
 */
int slot(int slotnumber, char *trameadecoder){//slot=nombre entre deux ';' selection du chiffre � extraire de la trame
    int i;//curseur parcourant la chaine re�u
    int var=0;//entier d�cod�
    int cptseparateur=0;//compte le nombre de ';'
    int pos=0;//0:gauche 1:droite
    int debut=0;//case debut d'un nb
    int fin=0;//case debut d'un nb
    char *p=trameadecoder;//pointeur de la trame re�u

    //part de 3 car avant c'est l'ent�te
    for(i=3;i<TAILLETRAME-1;i++){//parcourt de la chaine
        if((trameadecoder[i]==';') || (trameadecoder[i]=='\0')){//d�tection d'un s�parateur
            if(pos==0){//d�tection du ';' situ� � gauche du nombre (voir protocole)
               pos=1;//indique que le prochain ';' sera � droite
               debut=i;//donc c'est le d�but du nombre
               cptseparateur++;//on arrive dans un slot donc +1
            }else{////d�tection du ';' situ� � droite du nombre (voir protocole)
               pos=0;//indique que le prochain ';' sera � gauh=che
               fin=i;//donc c'est la fin du nombre
               if(cptseparateur == slotnumber){//si le compteur de slot atteint le slot demand�
                //coupe
                   var=substringsemicolon(debut, fin, p);//extraction de la chaine, debut + fin du slot + chaine
                   i=TAILLETRAME-1;//quite la boucle avant lorsque la valeur est extraite pour pas se taper toute la trame
               }else{//si c'est pas le slot demand�
                   pos=1;//d�calage du debut du slot avant de passer au suivant
                   debut=i;
                   cptseparateur++;
               }
            }
        }
    }
   return var;//entier extrait
}

//conversion d'une donn�e de la trame uart char*->int
int substringsemicolon(int debut,int fin, char *trame ){
    char subsstr[TAILLEVAL];//sous chaine extraite de la chaine principale
    int a=0;//curseur sous-chaine
    int b=0;//curseur chaine principale
    int var=-1;//en prevision d'une gestion d'erreur ?

    b=debut;//place le curseur au debut du slot
    while(b<fin){//tant que la fin du slot n'a pas �t� ateinte
        subsstr[a]=trame[b+1];//recopie des char de la chaine principale dans la sous chaine
        b++;
        a++;
    }
    var = atoi(subsstr);//conversion
    return var;//retour de l'entier
}

void delay (unsigned int ms)//fonction delai pas terrible
{
    volatile unsigned int i, z;
    i=100;
    while (i--) {
        z=ms;
        while(z--);
    }
}

//thx stackoverflow :)
void itoad(long unsigned int value, char *result, int base){//conversion entier en char*
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

