#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "interpreteur_uart_micro.h"
#include "interpreteur_uart_pc.h"
#include "util.h"

int forge(int nbvaleur,char type, int *dataint, char *trametx){//forge à utilisé plus tard avec concatenationdata
    int i=0;
    int cpt=0;
    int compteurtrame=4;
    char s[TAILLEVAL];
    int flag_overflow=0;//donnée utile a transmettre plus grand que la taille max autorisé par une seule trame

    trametx[0]='f';//1er caractere
    trametx[1]='2';
    trametx[2]=type;
    trametx[3]=';';
    //conversion int en char*
    for(i=0;i<nbvaleur;i++){
        //sprintf(s, "%d", dataint[i]); // Conversion de l'entier
        itoad(dataint[i], &s, 10);
        while(s[cpt] != '\0'){
            printf("%c",s[cpt]);
            trametx[compteurtrame]=s[cpt];
            cpt++;//compteur de la valeur en cours
            compteurtrame++;//compteyr du curseur dans la trame
        }
        cpt=0;
        printf("\n");
        if(i<nbvaleur-1){//bloquer le dernier ';'
            trametx[compteurtrame]=';';
            compteurtrame++;
        }
    }
    //printf(" compteur:%d \n ",compteurtrame);
    if(compteurtrame-2 >= TAILLETRAME-2 ){//-1 a cause de l'offset trametx[] et -2 car c'est la taille d'une trame -l le 1er carac -1 le dernier carac
        printf("overflow\n");
        flag_overflow=1;
    }else{
        trametx[compteurtrame]='\0';//fin de trame
        printf("-> ");
        for(i=0;i<TAILLETRAME;i++){//relecture afficage
            printf("%c",trametx[i]);
            if(trametx[i]=='\0'){
               printf("ok\n");
            }
        }
    }

return flag_overflow;
}
