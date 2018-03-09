/*
 * capteurInfrarouge.h
 *
 *  Created on: 9 mars 2018
 *      Author: Mathias
 */

#ifndef CAPTEURINFRAROUGE_H_
#define CAPTEURINFRAROUGE_H_

/*
 * exemple :
 *   ADC_init();
 *   ADC10AE0 |= BIT5;
 *   initInfrarouge();
 *
 *   volatile int detectionObstacle = 1000;//pour pas qu il s arrete pas au debut
 *   detectionObstacle = obstacle();
 */
void initInfrarouge();

/*
 * @return 1 si un obstable est détecter, 0 sinon
 */
int obstacle();

/*
 * Arrêt complet du robot
 */
void arreter();

/*
 * s'arrête si un obstacle est détecter,
 * repart et suit la ligne lorsque il n'y a plus d'obstacle
 */
void detacteObstacleEtArreter();



#endif /* CAPTEURINFRAROUGE_H_ */
