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

#include "RIT/RIT.h"         
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "./adc/adc.h"
#include "sample.h"
#include "joystick/joystick.h"
#include "GLCD/GLCD.h"
#include "TouchPanel/TouchPanel.h"
/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in lib_led								*/

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	//+++++++ data +++++++++++++
	
	
	//+++++++ init +++++++++++++
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec   RIT=100MHz clock   */
	enable_RIT();
	//++++++++ code ++++++++++++
	
																				/* All based on a 25Mhz CLK */
																				/* 10 ms x 25Mhz = 0x3D090 */
																				/* 100ms -> 0x2625A0 */
																				/* 120ms -> 0x2DC6C0 */
																				
	// INIT TIMER
	/* Stop - Reset - Interval
	 1 = Interval
	 2 = Reset
	 3 = Reset & Interval
	 5 = Stop & Interval
	 7 = Stop & Reset & Interval
	*/
	
	init_timer(1, 0x2887FA0, 0, 3); // Reset & interval, 0x2887FA0 = 1,7 * 25000000
  init_timer(2, 0x15C17540, 0, 2); // Reset	
	init_timer(0, 0x10B0760, 0, 3); // Reset & Interval, per controllare LED6, 700ms con toggle interno per decidere on-off

	enable_timer(2);
	enable_timer(1);

	//++++++++ power saving +++++++++
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);			
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }
}
