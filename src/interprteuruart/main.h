#define TAILLETRAME 16 //taille de la trame
#define TAILLEVAL 6 //val max+1 nombre de slot d'un entier
#define NOMBREDEVALEUR 2 //nombre de valueur a transmettre

#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

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

