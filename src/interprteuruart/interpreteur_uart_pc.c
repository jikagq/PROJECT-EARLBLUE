#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "interpreteur_uart_micro.h"
#include "interpreteur_uart_pc.h"
#include "util.h"

void forgemanuel(void){//forgage d'une trame � envoyer 0:type;1->14data;15 fin trame '\0'
    char c;
    int i;

    trametx[0]='t';

    printf("entrez des caractere %d delimier par ; si besoin\n",TAILLETRAME );
    for(i=1;i<TAILLETRAME-1;i++){//slot 0 = type de trame +carc de fin '\0'
        printf("> ");
        scanf("%c", &c);
        trametx[i]=c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    trametx[TAILLETRAME-1]='\0';

    printf("\n");
////////////////////////////////mettre le msp
    printf("-> ");
   for(i=0;i<TAILLETRAME;i++){//relecture afficage
        transmit(trametx[i]);
        printf("%c",trametx[i]);
    }
    raztrame();//trame envoyer donc raz
    receive();
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
