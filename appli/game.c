/*
 * game.c
 *
 *  Created on: 5 janv. 2022
 *      Author: kobeisch
 */

#include "config.h"
#include "game.h"
#include "bp.h"
#include "board.h"
#include "macro_types.h"
#include "WS2812S.h"
#include "AfficherLcd.h"
#include "GrilleDeJeu.h"




int CurrentJoueur = JOUEUR1;
int ModeDeJeu;



void init_game(){
	//Met l'etat de la LED jaune en HIGH
	HAL_GPIO_WritePin(GPIO_LED_YELLOW, PIN_LED_YELLOW, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIO_LED_RED, PIN_LED_RED, GPIO_PIN_RESET);

	//initialise le joueur 1 comme etant le joueur courant
	if(joueur() == JOUEUR2 || joueur() == ROBOT){
		CurrentJoueur = JOUEUR1;
	}

}


void ChoisirModeDeJeu(){
	button_id_e current_button;
	AffichageSelectionModeJeu();
	do{
		current_button = button_press_event();
		if(current_button == BUTTON_ID_LEFT){
			ModeDeJeu = IA;
		}
		else if(current_button == BUTTON_ID_RIGHT){
			ModeDeJeu = VS;
		}
	}
	while((current_button == BUTTON_ID_NONE) || (current_button == BUTTON_ID_VALIDATE));
	AffichageScore();
	GrilleDeJeu_init();
	init_game();
}



void ChangeJoueur(){
	if(CurrentJoueur == JOUEUR1 && ModeDeJeu == VS){
		CurrentJoueur = JOUEUR2;
		HAL_GPIO_WritePin(GPIO_LED_RED, PIN_LED_RED, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_LED_YELLOW, PIN_LED_YELLOW, GPIO_PIN_RESET);
	}
	else if(CurrentJoueur == JOUEUR2 && ModeDeJeu == VS ){
		CurrentJoueur = JOUEUR1;
		HAL_GPIO_WritePin(GPIO_LED_RED, PIN_LED_RED, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_LED_YELLOW, PIN_LED_YELLOW, GPIO_PIN_SET);
	}
	else if(CurrentJoueur == JOUEUR1 && ModeDeJeu == IA){
		CurrentJoueur = ROBOT;
		HAL_GPIO_WritePin(GPIO_LED_RED, PIN_LED_RED, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_LED_YELLOW, PIN_LED_YELLOW, GPIO_PIN_RESET);

	}
	else{
		CurrentJoueur = JOUEUR1;
		HAL_GPIO_WritePin(GPIO_LED_RED, PIN_LED_RED, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_LED_YELLOW, PIN_LED_YELLOW, GPIO_PIN_SET);
	}
}


int joueur(){
	return CurrentJoueur;

}


int get_ModeDeJeu(){
	return ModeDeJeu;
}




