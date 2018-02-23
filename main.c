
#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

#define TAILLETRAME 16 //taille de la trame
#define TAILLEVAL 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEUR 4 //nombre de valueur a transmettre

char    NomPort[50];        //nom du port
int     NumPort;            //numero du port
HANDLE  hCom;               //gestionnaire du port serie7
COMSTAT EtatCom;
DWORD   NbOctetsEcrits;
DWORD   NbOctetsLus;
int     NbOctetsALire;
int     retour;
DCB     dcb;	            //structure "Device-Control Block" definissant les parametres de la communication
char    chaine[10];         //chaine de 2 caracteres (pour WriteFile)

char trametx[TAILLETRAME];

int main(void)
{
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

void ledspi(){
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
    if(choixled == 1){

    }else{

    }
    if(){

    }else{

    }
    transmit();
    transmit();
    transmit();

}
//concatenationdata(a,b,c,d, &data);
void concatenationdata(int alpha, int beta, int charlie, int delta, int *dataint){// fonction exemple aquisition de 4 donnée a transmettre // max 7 slot//doit prendre exactement le nombre d'arg de data
//assume que il n'y a que 4 donnée a transmettre ne meme temps par tick
    int i;
    //NOMBREDEVALEUR





    dataint[4];//return du tableau de donné conca
}
//forge(carac,nb,&data,&trame);
void forge(char type, int *dataint, char *trametx){//forge à utilisé plus tard avec concatenationdata
    int i=0;
    int cpt=0;
    int compteurtrame=1;
    char s[TAILLEVAL];
    int flag_overflow=0;//donnée utile a transmettre plus grand que la taille max autorisé par une seule trame

    trametx[0]=type;//1er caractere

    //data<=TAILLETRAME-2//taille max des données utile

    //conversion int en char*
    for(i=0;i<NOMBREDEVALEUR;i++){
        sprintf(s, "%d", dataint[i]); // Conversion de l'entier
        while(s[cpt] != '\0'){
            printf("%c",s[cpt]);
            trametx[compteurtrame]=s[cpt];
            cpt++;//compteur de la valeur en cours
            compteurtrame++;//compteyr du curseur dans la trame
        }
        cpt=0;
        printf("\n");
        if(i<NOMBREDEVALEUR-1){//bloquer le dernier ';'
            trametx[compteurtrame]=';';
            compteurtrame++;
        }
    }
    //printf(" compteur:%d \n ",compteurtrame);
    if(compteurtrame-2 >= TAILLETRAME-2 ){//-1 a cause de l'offset trametx[] et -2 car c'est la taille d'une trame -l le 1er carac -1 le dernier carac
    printf("overflow\n");
    flag_overflow=1;
    }else{
        trametx[TAILLETRAME-1]='\0';//fin de trame
        printf("-> ");
        for(i=0;i<TAILLETRAME;i++){//relecture afficage
            printf("%c",trametx[i]);
            transmit(trametx[i]);
            if(trametx[i]=='\0'){
               printf("ok");
            }
        }
    }
    raztrame();
    receive();
return flag_overflow;
}
void forgemanuel(){//forgage d'une trame à envoyer 0:type;1->14data;15 fin trame '\0'
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
void raztrame(){
    int i;
    for(i=0;i<TAILLETRAME;i++){//relecture afficage
       trametx[i]=' ';
    }
}
void moniteur(){
    do{
        receive();
    }while(1);
}
void frequence(){
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
void led(){
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
void ping(){
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
void port(){
   int port;
   printf("le port par defaut est %d \n",NumPort);
   do{
        printf("saisissez une valeur entre 1 et 256 ");
        scanf("%d", &port);
    }while(port<0 || port >256);
    while ((port = getchar()) != '\n' && port != EOF);
    NumPort=port;
}
void inicom(){
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
