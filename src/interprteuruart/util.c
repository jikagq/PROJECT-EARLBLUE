#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "interpreteur_uart_micro.h"
#include "interpreteur_uart_pc.h"
#include "util.h"

void ledspi(void){
    int c;
    int choixled=1;
    int etat=0;

    do{
        printf("led 1 ou 2");
        scanf("%d", &c);
    }while((c != 1) && (c != 2));
    choixled=c;
    while ((c = getchar()) != '\n' && c!= EOF);
    printf("\n");
    do{
        printf("etat ? 0 ou 1");
        scanf("%d", &c);
    }while((c != 1) && (c != 2));
    etat=c;
    while ((c = getchar()) != '\n' && c!= EOF);
    printf("\n");
    printf("led:%d etat:%d", choixled,etat);
    transmit('y');
    /**if(choixled == 1){

    }else{

    }
    if(){

    }else{

    }
    transmit();
    transmit();
    transmit();**/

}
void raztrame(void){
    int i;
    for(i=0;i<TAILLETRAME;i++){//relecture afficage
       trametx[i]=' ';
    }
}
void moniteur(void){
    do{
        receive();
    }while(1);
}
void ping(void){
    int i;
    char ping[] = "ping";
    printf("-> %s", ping);
    transmit('c');
    for(i=0;i<5;i++){
    transmit(ping[i]);
    }
    receive();
}
void receive(void){
    char r;
    int t=0;
    printf("\n");
    Sleep(10);
    printf("<- ");
    do{
        NbOctetsALire=1;
        retour=ReadFile(hCom, &r, 1, &NbOctetsLus , NULL);   //lecture port serie
        if(!retour)
        {
            printf(" erreur ReadFile\n");
        }
        printf("%c", r);
    }while(r != '\0');
    printf("\n");
}
void transmit(char c){
    sprintf(chaine, "%c", c);
    retour=WriteFile(hCom, chaine, 1, &NbOctetsEcrits, NULL);   //ecriture dans port serie
    if(!retour)
    {
        printf(" erreur WriteFile\n");
    }
}
void port(void){
   int port;
   printf("le port par defaut est %d \n",NumPort);
   do{
        printf("saisissez une valeur entre 1 et 256 ");
        scanf("%d", &port);
    }while(port<0 || port >256);
    while ((port = getchar()) != '\n' && port != EOF);
    NumPort=port;
}
void inicom(void){
    NumPort=2;                     //a adapter
	//-----------ouverture------------------
	sprintf(NomPort, "\\\\.\\COM%d", NumPort);
	hCom=CreateFile(NomPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	//CloseHandle(hCom);
	if(hCom==INVALID_HANDLE_VALUE)
	{
        printf("erreur CreateFile\n");
        return -1;
	}
    printf("CreateFile OK\n");
	//------------configuration-------------
	retour=GetCommState(hCom, &dcb);    //lecture des parametres actuels du port
	if(retour==0)
	{
	    printf("erreur GetCommState\n");
        exit(1);
	}
    printf("GetCommState OK\n");
	dcb.ByteSize=8;			            //nombre de bits de donnee
	dcb.StopBits=1;			            //nombre de bit(s) de stop
	dcb.Parity=NOPARITY;				//type de parite
	dcb.BaudRate=9600;				    //vitesse de transfert des donnees
                                        //ou 110, 150, 300, 600, 1200, 1800, 2400, 2800, 7200, 9600, 14400, 19200,
                                        // 38400, 57600, 115200, 128000, 256000
	retour=SetCommState(hCom, &dcb);    //ecriture de ces parametres
	if(retour==0)
	{
	    printf("erreur SetCommState\n");
        exit(1);
	}
    printf("SetCommState OK\n");
}
void itoad(long unsigned int value, char *result, int base){//existe déja dans stdlib.h ???
      // check that the base if valid
      if (base < 2 || base > 36){
            *result = '\0';
      }
      char *ptr = result, *ptr1 = result, tmp_char;
      int tmp_value;

      do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
      } while ( value );

      // Apply negative sign
      if (tmp_value < 0) *ptr++ = '-';
      *ptr-- = '\0';
      while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
      }

    }
