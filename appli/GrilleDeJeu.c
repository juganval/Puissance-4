/*
 * GrilleDeJeu.c
 *
 *  Created on: 5 janv. 2022
 *      Author: kobeisch
 */


#include "GrilleDeJeu.h"
#include "WS2812S.h"
#include "board.h"
#include "macro_types.h"
#include "bp.h"
#include "game.h"
#include "stm32f1xx_hal.h"
#include "AfficherLcd.h"
#include "IA.h"

uint32_t pixels[64];
int jetonSel = 60;


//Initialise la grille de jeu en, le joueur jaune commence.
void GrilleDeJeu_init(){
	//initialise la matrice de LED
	LED_MATRIX_init();
	jetonSel = 60;

	//Allume une led sur la ligne 64 à 57 (vers le milieu)
	uint8_t i;
	for(i=0;i<64;i++){
		pixels[i] = COLOR_BLACK;
	}
	pixels[jetonSel] = COLOR_YELLOW;
	LED_MATRIX_display(pixels, 64);
}





//Fonction qui gere les appuis sur le bouton poussoir de Gauche
void Selec_G(){
	if(jetonSel < 63 && jetonSel >= 56 /*&& joueur() != ROBOT */){
		pixels[jetonSel] = COLOR_BLACK;
		LED_MATRIX_display(pixels, 64);
		jetonSel += 1;
		if(joueur() == 1){
			pixels[jetonSel] = COLOR_YELLOW;
			LED_MATRIX_display(pixels, 64);
		}
		else{
			pixels[jetonSel] = COLOR_RED;
			LED_MATRIX_display(pixels, 64);
		}
	}
}



//Fonction qui gere les appuis sur le bouton poussoir de droite
void Selec_D(){
	if(jetonSel > 56 && jetonSel <= 64 /* && joueur() != ROBOT */){
		pixels[jetonSel] = COLOR_BLACK;
		LED_MATRIX_display(pixels, 64);
		jetonSel -= 1;
		if(joueur() == 1){
			pixels[jetonSel] = COLOR_YELLOW;
			LED_MATRIX_display(pixels, 64);
		}
		else{
			pixels[jetonSel] = COLOR_RED;
			LED_MATRIX_display(pixels, 64);
		}
	}
}



//Fonction qui gere la validation de la colone que l'on souhaite jouer
void Selec_Validate(){
	while( pixels[jetonSel - 8] == COLOR_BLACK && jetonSel - 8 >= 0 /*&& joueur() != ROBOT */){
		pixels[jetonSel] = COLOR_BLACK;
		LED_MATRIX_display(pixels, 64);
		if(joueur() == JOUEUR1){
			jetonSel -= 8;
			pixels[jetonSel] = COLOR_YELLOW;
			LED_MATRIX_display(pixels, 64);
			HAL_Delay(50);
		}
		else{
			jetonSel -= 8;
			pixels[jetonSel] = COLOR_RED;
			LED_MATRIX_display(pixels, 64);
			HAL_Delay(50);
		}
	}
	if(verificationLigne()  || verificationColonne() || verificationDiagonale()){
		HAL_Delay(5000);
		incrementScore();
		GrilleDeJeu_init();
		init_game();


		// + incrémenter le score de 1 pour le joueur
	}
	else if(jetonSel < 56){
		ChangeJoueur();
		NouveauPion();
		verification();
	}

}



//Fonction qui s'occupe d'allumer une nouvelle led (de la bonne couleur) de selection lorsque l'adversere a joué
void NouveauPion(){
	jetonSel = 60;
	if(joueur() == JOUEUR1){
		pixels[jetonSel] = COLOR_YELLOW;
		LED_MATRIX_display(pixels, 64);
	}
	else if(joueur() == JOUEUR2 ){
		pixels[jetonSel] = COLOR_RED;
		LED_MATRIX_display(pixels, 64);
	}
	else if(joueur() == ROBOT){
		pixels[jetonSel] = COLOR_RED;
		LED_MATRIX_display(pixels, 64);
		IAJeu(); //appel de la focntion IA (random )
	}
}



//Verifie si la grille de jeu est complète et que personne a gagné
void verification(){
	int q = 1;
	int reset = 0;
	for(q = 1; q <57; q++){
		if(pixels[q] != COLOR_BLACK /*Rajouter : et que la partie n'est pas gagnée*/ ){
			reset +=1;
		}
		if(reset >= 55){
			GrilleDeJeu_init();
		}
	}
}


//Verifie si 4 pions de la même couleur sont alignés sur la même ligne
bool_e verificationLigne(){
	for (int i = 0; i<53; i++){
		if (pixels[i] == COLOR_YELLOW && pixels[i+1] == COLOR_YELLOW && pixels[i+2] == COLOR_YELLOW && pixels[i+3] == COLOR_YELLOW && i % 8 < 5){
			return 1;
			}
		else if (pixels[i] == COLOR_RED && pixels[i+1] == COLOR_RED && pixels[i+2] == COLOR_RED && pixels[i+3] == COLOR_RED && i % 8 < 5){
			return 1;
		}
	}
	return 0;
}



//Verifie si 4 pions de la même couleur sont alignés sur la même colonne
bool_e verificationColonne(){
	for (int i = 1; i<32; i++){
			if (pixels[i] == COLOR_YELLOW && pixels[i+8] == COLOR_YELLOW && pixels[i+16] == COLOR_YELLOW && pixels[i+24] == COLOR_YELLOW && i <= 40){
				return 1;

				}
			if (pixels[i] == COLOR_RED && pixels[i+8] == COLOR_RED && pixels[i+16] == COLOR_RED && pixels[i+24] == COLOR_RED && i <= 40){
				return 1;
			}
	}
	return 0;
}


//Verifie si 4 pions de la même couleur sont alignés sur une diagonale
bool_e verificationDiagonale(){
	for (int i = 1; i<29; i++){
		if (pixels[i] == COLOR_YELLOW && pixels[i+9] == COLOR_YELLOW && pixels[i+18] == COLOR_YELLOW && pixels[i+27] == COLOR_YELLOW && i % 8 < 5){
			return 1;
			}

		else if (pixels[i] == COLOR_RED && pixels[i+9] == COLOR_RED && pixels[i+18] == COLOR_RED && pixels[i+27] == COLOR_RED && i % 8 < 5){
			return 1;
		}
	}
	for(int k = 3 ; k <32 ; k++){
		if (pixels[k] == COLOR_YELLOW && pixels[k+7] == COLOR_YELLOW && pixels[k+14] == COLOR_YELLOW && pixels[k+21] == COLOR_YELLOW && k % 8 > 2){
			return 1;
		}
		else if (pixels[k] == COLOR_RED && pixels[k+7] == COLOR_RED && pixels[k+14] == COLOR_RED && pixels[k+21] == COLOR_RED && k % 8 > 2){
			return 1;
		}
	}
	return 0;
}


int get_jetonSel(){
	return jetonSel;
}

bool_e detect_pb(int nb){
	if((pixels[nb-8] == COLOR_YELLOW) || (pixels[nb-8] == COLOR_RED)){
		return TRUE;
	}
	else{
		return FALSE;
	}
}




