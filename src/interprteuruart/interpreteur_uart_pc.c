#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "interpreteur_uart_micro.h"
#include "interpreteur_uart_pc.h"
#include "util.h"

void forgemanuel(char *trametx){//forgage d'une trame à envoyer 0:type;1->14data;15 fin trame '\0'
    char c='a';
    int i;
    int fin=0;
    trametx[0]='f';//indic que c'est une trame forge

    printf("entrez des caractere %d delimier par ; si besoin * termine la trame\n",TAILLETRAME );
    for(i=1;i<TAILLETRAME-1;i++){//slot 0 = type de trame +carc de fin '\0'
        if(fin==1){//fin demandé par l'utilisateur
            trametx[i]='\0';
        }else{
            printf("> ");
            scanf("%c", &c);
            if(c=='*'){
                fin=1;
            }else{
                trametx[i]=c;
                while ((c = getchar()) != '\n' && c != EOF);
            }

        }

    }
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\n");
////////////////////////////////mettre le msp
    printf("-> ");
   for(i=0;i<TAILLETRAME;i++){//relecture afficage
        printf("%c",trametx[i]);
    }
}
void frequence(void){
    int tpsh=1000;
    int tpsb=1000;
    int freq;

    do{
        printf("temps etat haut\n");
        printf("\n> ");
        scanf("%d", &freq);
    }while((tpsh<0) || (tpsh>1000) );
    tpsh=freq;
    //printf("%d",tpsh);
    while ((freq = getchar()) != '\n' && freq != EOF);

    do{
        printf("temps etat bas\n");
        printf("\n> ");
        scanf("%d", &freq);
    }while((tpsb<0) || (tpsb>1000) );
    tpsb=freq;
    //printf("%d",tpsb);
    while ((freq = getchar()) != '\n' && freq != EOF);


}
void led(void){
    int onoffled1=0;
    int i=0;
    do{
        printf("1 pour allumer, 0 pour eteindre la led ");
        scanf("%d", &onoffled1);
    }while((onoffled1 != 0) && (onoffled1 != 1));

    do{
        printf("1 pour allumer, 0 pour eteindre la led ");
        scanf("%d", &onoffled1);
    }while((onoffled1 != 0) && (onoffled1 != 1));

    printf("-> %d", onoffled1);
    transmit('L');
    if(onoffled1==1){
        transmit('1');
    }else{
        transmit('0');
    }
    transmit('\0');

    while ((onoffled1 = getchar()) != '\n' && onoffled1 != EOF);
    receive();
}
