/*
 * capteurInfrarouge.h
 *
 *  Created on: 9 mars 2018
 *      Author: Mathias
 */

#ifndef CAPTEURINFRAROUGE_H_
#define CAPTEURINFRAROUGE_H_

#define SEUILOBSTACLE 350
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

int aquisition();

#endif /* CAPTEURINFRAROUGE_H_ */
