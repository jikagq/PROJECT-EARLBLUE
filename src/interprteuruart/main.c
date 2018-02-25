/***********************************************/
/* to do list: -gerer l'overflow et faire repeter la trame*/
/*  -ajouter un champs longueur*/
/* -ajouter un champs nb d'element*/
/*
/**********************************************/


#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "interpreteur_uart_micro.h"
#include "interpreteur_uart_pc.h"
#include "util.h"


int main(void){
    int i;
    char caracAtransmettre;
    inicom();
    i=0;
    menu();
	CloseHandle(hCom);					//fermeture du gestionnaire de port (jamais atteint !)
    return 0;
}
void menu(void){

int r;
char choix;
char c;
printf("*==================================================*\n");
printf("*                 interpreteur UART                *\n");
printf("*==================================================*\n");
////////////test////////////
/**int datainttest[]={46,688,885,564};
forge('a',&datainttest,&trametx);//obliger d'avoir le nombre de valeur exact**/

/**int val;
char str[]="1000";
val = atoi(str);
printf("%d",val);**/

/**int test=46;
char string[5];
itoad(test,&string,10);
printf("entier:%d string:%s",test,string);**/
///////////test////////////

printf("Taper 'h' pour l'aide\n");
printf("->send to uc\n");
printf("<-receive from uc\n");
do{
  printf("\n> ");
  scanf("%c", &c);
  choix=c;
  while ((c = getchar()) != '\n' && c != EOF);

  switch(choix){
   case 'h':{//aide
        printf("Actions possibles:\n");
        printf("\n");
        printf("p: changer le port\n");
        printf("c: verif com(ping)\n");
        printf("l: allumer la led\n");
        printf("t: forge manuelle trame (echo)\n");
        printf("y: ledspi\n");
        printf("m: moniteur serie\n");
        printf("f: changer la frequence de cli\n");
        printf("i: reinini\n");
        printf("d: disconnect\n");
        printf("e: quiter\n");
        break;
        }
  case 'p':{//changer le port
        port();
        CloseHandle(hCom);
        inicom();
        break;
        }
  case 'c':{//ping
        ping();
        break;
        }
  case 'e':{
        break;//quiter
        }
  case 'm':{
        moniteur();
        break;//quiter
        }
  case 'y':{
        ledspi();
        break;//quiter
        }
  case 't':{
        forgemanuel();
        break;//quiter
        }
  case 'f':{
        frequence();
        break;//quiter
        }
  case 'i':{//rini
        inicom();
        break;
        }
  case 'd':{//deco
        printf("deconnexion\n");
        CloseHandle(hCom);
        break;
        }
  case 'l':{//led
        led();
        break;
        }
  default :{
        printf("Commande invalide taper h pour l'aide\n");
        break;
        }
  }
}while(choix != 'e');
}
