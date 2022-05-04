/*
 * AfficherLcd.c
 *
 *  Created on: 5 janv. 2022
 *      Author: kobeisch
 */

#include "lcd2x16.h"
#include "AfficherLcd.h"
#include "GrilleDeJeu.h"
#include "game.h"
#include "macro_types.h"
#include "stm32f1xx_hal.h"
#include "bp.h"

int scoreJ1 = 0;
int scoreJ2 = 0 ;





void AfficherLcd_init(){
//Initialise la matrice de LED
	LCD2X16_init();
	LCD2X16_setCursor(2,1);
	LCD2X16_printf("Bienvenue sur");
	LCD2X16_setCursor(2,2);
	LCD2X16_printf("Puissance L4D");
	HAL_Delay(5000);
	LCD2X16_init();
	ChoisirModeDeJeu();
}



void AffichageSelectionModeJeu(){
	LCD2X16_setCursor(1,1);
	LCD2X16_printf("Choisir le mode de jeu");
	LCD2X16_setCursor(1,2);
	LCD2X16_printf(" IA ");
	LCD2X16_setCursor(11,2);
	LCD2X16_printf(" VS ");
}


//permet l'affichage du score
void AffichageScore(){
	LCD2X16_init();
	//Met à jour l'affichage de l'écran
	LCD2X16_setCursor(6,1);
	LCD2X16_printf("Scores");

	//Met les scores de l'écran à 0
	LCD2X16_setCursor(1,2);
	LCD2X16_printf("J1: ");
	LCD2X16_setCursor(4,2);
	LCD2X16_printf("%02d", scoreJ1);

	if(get_ModeDeJeu() == 2){
		LCD2X16_setCursor(11,2);
		LCD2X16_printf("J2: ");
		LCD2X16_setCursor(14,2);
		LCD2X16_printf("%02d", scoreJ2);
	}
	else{
		LCD2X16_setCursor(11,2);
		LCD2X16_printf("IA: ");
		LCD2X16_setCursor(14,2);
		LCD2X16_printf("%02d", scoreJ2);
	}

}



void incrementScore(){
	if(joueur() == 1){
		scoreJ1 += 1;
		LCD2X16_setCursor(1,2);
		LCD2X16_printf("J1: ");
		LCD2X16_setCursor(4,2);
		LCD2X16_printf("%02d", scoreJ1);//incrémenter le score de 1
	}
	else if(joueur() == 2){
		scoreJ2 += 1;
		LCD2X16_setCursor(11,2);
		LCD2X16_printf("J2: ");
		LCD2X16_setCursor(14,2);
		LCD2X16_printf("%02d", scoreJ2);	//incrémenter le score de 1
	}
	else if(joueur() == 3){
		scoreJ2 += 1;
		LCD2X16_setCursor(11,2);
		LCD2X16_printf("IA: ");
		LCD2X16_setCursor(14,2);
		LCD2X16_printf("%02d", scoreJ2);
	}
}
