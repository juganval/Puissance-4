/*
 * jeux.h
 *
 *  Created on: 5 janv. 2022
 *      Author: kobeisch
 */

#ifndef GAME_H_
#define GAME_H_

//ID joueurs
#define JOUEUR1		1
#define JOUEUR2		2
#define ROBOT		3

//Mode de jeu
#define IA 		1
#define VS 		2



void init_game();

void ChangeJoueur();

int joueur();

void ChoisirModeDeJeu();

int get_ModeDeJeu();

#endif /* GAME_H_ */
