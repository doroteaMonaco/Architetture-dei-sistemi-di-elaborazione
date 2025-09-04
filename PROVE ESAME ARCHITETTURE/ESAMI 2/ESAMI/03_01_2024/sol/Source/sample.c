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


volatile int  Matrix_Coordinates[];   scrivo tutte le variabili globali come volatile e poi come extern nel .h, così includendolo nell'altro .c posso usare queste variabili
volatile uint8_t   ROWS[];
volatile uint8_t   COLUMNS[];

voltile unsigned char led_value;
*/

//DA METTERE NELLE GLOBALI CONDIVISE --> volatile = si utilizza quando una variabile può essere modificata da un'entità esterna al normale flusso del programma
//DA METTERE NELLE FUNZIONI --> static = mantiene il valore della variabile in un blocco, si comporta come una variabile GLOBALE nel singolo blocco/funzione e al di fuori di essa 
//NON è visibile

#define N 10
#define M 14

unsigned char ExtractVal(int value); //estraggo 8 bit
unsigned char check_fibonacci(unsigned char* vett, unsigned char N1, unsigned char M1, unsigned char val, unsigned char BOUNDARY1); //controllo correttezza value
void fill_fibonacci(unsigned char M1); //riempio il vettore fibonacci
void clean_vett(); //per pulire il vettore


int first=1; //la prima volta che entro nel RIT avvio il timer

unsigned char vett[N];



int main (void) {
	
	//call_svc();    chiamata naked di una SVC

  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x1312D0);									/* RIT Initialization 50 msec       	*/
	//enable_RIT();													/* RIT enabled												*/
	
	//SRI per inizializzazione timer
	/*LETTURA TC
		disable_timer(2); 
		value = LPC_TIM2->TC; //lettura di TC 
		enable_timer(2);*/
	fill_fibonacci(M); //riempio vettore fibonacci
	init_timer(2, 0, 0, 0x2, 0x997B61C0); //inizializzo timer2 ogni 103secondi da cui prendere TC
	init_timer(1, 0, 0, 0x5, 0x4C4B40); //timer 1 per periodo 2s->0x2FAF080 in cui key è disabilitato
	init_timer(3, 0, 0, 0x3, 0x12B128); //timer ogni 490ms->0xBAEB90 per far lampeggiare i led con value
	init_timer(0, 0, 0, 0x3, 0x198EF8); //timer ogni 0.67s->0xFF95B0 per far lampeggiare i led con discard


	
	//LED_Out(0xFF) accendo tutti i led

	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);			
	
	
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}

void clean_vett() {
	int i;
	for(i=0;i<N;i++) {
		vett[i]=0;
	}
		
}
