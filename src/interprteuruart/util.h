#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>

void ledspi(void);
void raztrame(void);
void moniteur(void);
void ping(void);
void receive(void);
void transmit(char c);
void port(void);
void inicom(void);
void itoad(long unsigned int value, char *result, int base);
void sendtrameuart(char *trametx);
