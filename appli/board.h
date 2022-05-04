/*
 * board.h
 *
 *  Created on: 5 janv. 2022
 *      Author: kobeisch
 */


#ifndef BOARD_H_
#define BOARD_H_





//définition des leds
#define GPIO_LED_YELLOW			GPIOA				//LED Gauche jaune
#define PIN_LED_YELLOW			GPIO_PIN_9

#define GPIO_LED_RED			GPIOA				//LED Droite rouge
#define PIN_LED_RED				GPIO_PIN_10


//définitions des boutons poussoirs
#define GPIO_BUTTON_LEFT		GPIOA			//Bouton gauche
#define PIN_BUTTON_LEFT			GPIO_PIN_8

#define GPIO_BUTTON_RIGHT		GPIOB			//Bouton Droit
#define PIN_BUTTON_RIGHT		GPIO_PIN_14

#define GPIO_BUTTON_VALIDATE	GPIOB		//Bouton Milieu (Validé)
#define PIN_BUTTON_VALIDATE		GPIO_PIN_15




void  BOARD_Init();


#endif /* BOARD_H_ */
