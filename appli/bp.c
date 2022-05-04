/*
 * bp.c
 *
 *  Created on: 15 déc. 2021
 *      Author: kobeisch
 */

#include "config.h"
#include "macro_types.h"
#include "bp.h"
#include "board.h"
#include "GrilleDeJeu.h"




button_id_e button_press_event(void)
{
	static bool_e previous_state[BUTTON_ID_NB] = {FALSE};
	button_id_e ret = BUTTON_ID_NONE;
	button_id_e button_id;
	bool_e current_state;
	for(button_id = BUTTON_ID_LEFT; button_id<BUTTON_ID_NB; button_id++)
	{
		switch(button_id)
		{
		case BUTTON_ID_LEFT:
			current_state = !HAL_GPIO_ReadPin(GPIO_BUTTON_LEFT,PIN_BUTTON_LEFT);
			break;
		case BUTTON_ID_RIGHT:
			current_state = !HAL_GPIO_ReadPin(GPIO_BUTTON_RIGHT,PIN_BUTTON_RIGHT);
			break;
		case BUTTON_ID_VALIDATE:
			current_state = !HAL_GPIO_ReadPin(GPIO_BUTTON_VALIDATE,PIN_BUTTON_VALIDATE);
			break;
		default:
			current_state = 0; break;
		}
		if(current_state && !previous_state[button_id])
			ret = button_id;
		previous_state[button_id] = current_state;
	}
	return ret;
}




//Detecte sur quel bouton l'on appuis, et renvoie sur la fonction associé au bouton
void button(){
		button_id_e current_button = button_press_event();
		if(current_button == BUTTON_ID_LEFT){
			Selec_G();

		}
		else if(current_button == BUTTON_ID_RIGHT){
			Selec_D();
		}
		else if(current_button == BUTTON_ID_VALIDATE){
			Selec_Validate();
		}
}
