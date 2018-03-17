/*
 * ADC.h
 *
 *  Created on: 9 mars 2018
 *      Author: Mathias
 */

#ifndef ADC_H_
#define ADC_H_
/*
 * Initialise l'ADC
 */
void ADC_init(void);

/*
 * Démarre l'acquisition par l'ADC
 */
void ADC_Demarrer_conversion(unsigned char voie);

/*
 * Lire les résultats de l'ADC
 */
int ADC_Lire_resultat ();


#endif /* ADC_H_ */
