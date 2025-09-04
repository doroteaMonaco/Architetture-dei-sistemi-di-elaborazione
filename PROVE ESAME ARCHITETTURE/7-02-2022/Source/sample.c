/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through debounced buttons and Joystick
 *        	- key1 switches on the led at the left of the current led on, 
 *					- it implements a circular led effect,
 * 					- joystick UP function returns to initial configuration (led11 on) .
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

extern void call_svc(void);

/* UTILE per manipolare MATRICI
int check_square(int, int, int);  
float my_division(float*,float*);


volatile int  Matrix_Coordinates[];   scrivo tutte le variabili globali come volatile e poi come extern nel .h, cos� includendolo nell'altro .c posso usare queste variabili
volatile uint8_t   ROWS[];
volatile uint8_t   COLUMNS[];

voltile unsigned char led_value;
*/

//DA METTERE NELLE GLOBALI CONDIVISE --> volatile = si utilizza quando una variabile pu� essere modificata da un'entit� esterna al normale flusso del programma
//DA METTERE NELLE FUNZIONI --> static = mantiene il valore della variabile in un blocco, si comporta come una variabile GLOBALE nel singolo blocco/funzione e al di fuori di essa 
//NON � visibile

void bubbleSort(int arr[], int n);
unsigned int S = 0, N = 0, I = 0;
char pI = 0, pS = 0, pN = 0;
int stat_satisfaction(unsigned int S, unsigned int N, unsigned int I, char *pS, char *pN, char *pI);

int main (void) {
	
	//call_svc();    chiamata naked di una SVC

  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x1312D0);									/* RIT Initialization 50 msec       	*/
	enable_RIT(); //solo se ho il joystick
	//SRI per inizializzazione timer
	/*LETTURA TC
		disable_timer(2); 
		value = LPC_TIM2->TC; //lettura di TC 
		enable_timer(2);
	*/

	init_timer(0, 0, 0, 3, 0x17D7840); //MR0  calcolo K/2, dopo il quale scatena l'evento, ho I attivato per entrare nell'handler
	init_timer(1, 0, 0, 5, 0x2FAF080); //MR1	calcolo K=T*Fr=(1/60Hz)*25*10^6, dopo ogni K scatena l'evento e resetta il timer (R attivato), ho I attivato per entrare nell'handler
	init_timer(2, 0, 0, 3, 0x2625A0);
	init_timer(3, 0, 0, 3, 0x2FAF080);
	//enable_timer(0); //Attivo timer
	
	//LED_Out(0xFF) accendo tutti i led
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}

void bubbleSort(int arr[], int n) {
    int i, j, temp;

    // Ciclo per passare attraverso tutti gli elementi
    for (i = 0; i < n - 1; i++) {
        // Ciclo interno per confrontare elementi adiacenti
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Scambio degli elementi se non sono nell'ordine corretto
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

