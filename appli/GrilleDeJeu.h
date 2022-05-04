/*
 * GrilleDeJeu.h
 *
 *  Created on: 5 janv. 2022
 *      Author: kobeisch
 */

#ifndef GRILLEDEJEU_H_
#define GRILLEDEJEU_H_
#include "macro_types.h"

#define COLOR_BLUE	0x0000FF
#define COLOR_RED	0x002200
#define COLOR_GREEN	0xFF0000
#define COLOR_BLACK	0x000000
#define COLOR_YELLOW 0x0F1C00



//Initialise la grille de jeu
void GrilleDeJeu_init();



//Fonction qui gere les appuis sur le bouton poussoir de droite
void Selec_D();



//Fonction qui gere les appuis sur le bouton poussoir de Gauche
void Selec_G();


//Fonction qui gere la validation de la colone que l'on souhaite jouer
void Selec_Validate();


//Verifie si la grille de jeu est complète et que personne a gagné
void verification();


//Les fonction ci-dessous verifie, les lignes, les colonnes et les diagonales pour savoir si 4 pions sont alignés
bool_e verificationLigne();
bool_e verificationDiagonale();
bool_e verificationColonne();



//Fonction qui s'occupe d'allumer une nouvelle led (de la bonne couleur) de selection lorsque l'adversere a joué
void NouveauPion();

int get_jetonSel();

bool_e detect_pb();


#endif /* GRILLEDEJEU_H_ */
