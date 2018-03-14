/*
 * drivermoteur.h
 *
 *  Created on: 9 mars 2018
 *      Author: theo-
 */

#ifndef DRIVERMOTEUR_H_
#define DRIVERMOTEUR_H_


extern volatile int valgauche;
extern volatile int valdroite;


extern void initmoteur(void);
extern void avancer(void);
extern void reculer(void);
extern void droite(void);
extern void gauche(void);
extern void stop(void);
extern void testmoteur(void);
extern void droiteauto(int pas);
extern void gaucheauto(int pas);

#endif /* DRIVERMOTEUR_H_ */
