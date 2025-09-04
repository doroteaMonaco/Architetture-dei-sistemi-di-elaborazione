/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: 
 *		to control led11 and led 10 through EINT buttons (similarly to project 03_)
 *		to control leds9 to led4 by the timer handler (1 second - circular cycling)
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/

                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include <stdint.h>

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in lib_led								*/
#define N 7000
uint32_t v[N];
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	
	LPC_SC -> PCONP |= (1 << 22);  // TURN ON TIMER 2
	LPC_SC -> PCONP |= (1 << 23);  // TURN ON TIMER 3	


//	init_timer(2, 0, 2, 1, 0x017D7840);							/* TIMER0 Initialization              */
																				/* K = T*Fr = (1/75)*25*10^6	  */
																				/* T = K / Fr = 0x017D7840 / 25MHz    */
																				/* T = K / Fr = 25000000 / 25MHz      */
																				/* T = 1s	(one second)   							*/							
	//enable_timer(2);
	//LED_Out(0xFF) accende tutti i LED //Frequenza 30Hz
	init_timer(2, 0, 0, 1, 0x65B9A); //MR0  
	init_timer(2, 0, 1, 3, 0xCB735); //MR1
	
	enable_timer(2);

//Frequenza 75Hz
	init_timer(3, 0, 0, 1, 0x28B0A); //MR0
	init_timer(3, 0, 1, 3, 0x51615); //MR1
	
	enable_timer(3);

//	init_timer(2, 0, 0, 7, 0x47868C0);
//	enable_timer(2);

	enable_timer(0);
	
	init_timer(1, 0, 0, 3, 0x1046); //MR0
	
	enable_timer(1);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= 0xFFFFFFFFD;						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}


//	LPC_SC->PCONP |= (1 << 22); // Enable Timer 2
//  LPC_SC->PCONP |= (1 << 23); // Enable Timer 3