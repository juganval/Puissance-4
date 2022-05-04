/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "lcd2x16.h"
#include "bp.h"
#include "board.h"
#include "game.h"
#include "AfficherLcd.h"
#include "GrilleDeJeu.h"
#include "IA.h"

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
	HAL_Init();


	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);


	//initialisation des boutons poussoirs, des leds
	BOARD_Init();


	init_IA();

	//Initialisation de l'affiache de l'ecran LCD avec un message de "bienvenue" puis par l'affichage prénliminaire des scores initialisé a 0
	AfficherLcd_init();

	//Initialisation de la grille de jeu
	//GrilleDeJeu_init();

	//Initilise le joueur courant comme étant le Joueur 1 et allume la led jaune
	//init_game();


	//LCD2X16_demo();

	while(1)	//boucle de tâche de fond
	{
		button();

//		button_id_e current_button = button_press_event();
//		if(current_button == BUTTON_ID_LEFT){
//			HAL_GPIO_WritePin(GPIO_LED_YELLOW, PIN_LED_YELLOW, GPIO_PIN_SET);
//
//		}
//		else if(current_button == BUTTON_ID_RIGHT){
//			HAL_GPIO_WritePin(GPIO_LED_RED, PIN_LED_RED, GPIO_PIN_SET);
//		}
//		else if(current_button == BUTTON_ID_VALIDATE){
//			HAL_GPIO_TogglePin(GPIO_LED_YELLOW, PIN_LED_YELLOW);
//			HAL_GPIO_TogglePin(GPIO_LED_RED, PIN_LED_RED);
//		}

		//LED_MATRIX_demo();

	}
}





