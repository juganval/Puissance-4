/*
 * IA.c
 *
 *  Created on: 14 janv. 2022
 *      Author: kobeisch
 */



#include "systick.h"
#include "GrilleDeJeu.h"
#include "stm32f1xx_hal.h"


static volatile int var_random = 0;

void temps_ms()
{
	var_random++;
}

void init_IA()
{
	Systick_add_callback_function(&temps_ms);
}

/*void RandomJeu(){
	///renvoi un nombre aléatoire entre 0 et nb
	int nb = 57;
	return SYSTICK_get_time_us() % nb;
}*/



void IAJeu(){
	int nb;
	int nb_err = 56;
	nb = var_random % 8 +56;
	while(detect_pb(nb))
	{
		nb_err++;
		nb = nb_err;

	}
	while( (nb < 61) && nb > 57 &&  (nb != get_jetonSel() + 1 )){
		Selec_D();
		HAL_Delay(500);
	}
	while( (nb > 61) && nb <= 63 && (nb != get_jetonSel() + 1 )){
		Selec_G();
		HAL_Delay(500);
	}
	Selec_Validate();



/*int get_nb(){
	return nb;*/
}


//	while( pixels[nb - 8] == COLOR_BLACK && nb - 8 >= 0 && joueur() == ROBOT){
//		pixels[nb] = COLOR_BLACK;
//		LED_MATRIX_display(pixels, 64);
//		nb -= 8;
//		pixels[nb] = COLOR_RED;
//		LED_MATRIX_display(pixels, 64);
//		HAL_Delay(50);
//
//	}

