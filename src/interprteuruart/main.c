/***********************************************/
/* to do list: -gerer l'overflow et faire repeter la trame*/
/*
/*
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
//int datainttest[]={1,1000};
//forge(2,'l',&datainttest,&trametx);//obliger d'avoir le nombre de valeur exact
//sendtrameuart(&trametx);

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
        printf("!: commande manuel\n");
        printf("t: forge manuelle trame (echo)\n");
        printf("y: ledspi\n");
        printf("o: moniteur serie\n");
        printf("m: change mode\n");
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
  case 'm':{//ping
        changemode();
        sendtrameuart(&trametx);
        break;
        }
  case 'e':{
        break;//quiter
        }
  case 'o':{
        moniteur();
        break;//quiter
        }
  case 'y':{
        ledspi();
        break;//quiter
        }
  case 't':{
        forgemanuel(&trametx);
        sendtrameuart(&trametx);
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
  raztrame();
}while(choix != 'e');
}
