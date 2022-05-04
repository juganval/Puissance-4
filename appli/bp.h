/*
 * bp.h
 *
 *  Created on: 15 déc. 2021
 *      Author: kobeisch
 */

#ifndef BP_H_
#define BP_H_

#include "stm32f1xx_hal.h"



typedef enum
{
	BUTTON_ID_NONE = 0,
	BUTTON_ID_LEFT,
	BUTTON_ID_RIGHT,
	BUTTON_ID_VALIDATE,
	BUTTON_ID_NB
}button_id_e;


button_id_e button_press_event(void);

//Detecte sur quel bouton l'on appuis, et renvoie sur la fonction associé au bouton
void button();



#endif /* BP_H_ */
