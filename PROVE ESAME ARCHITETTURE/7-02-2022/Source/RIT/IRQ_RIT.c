/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "stdint.h"
#include "led/led.h"
#include "LPC17xx.h"
#include "RIT.h"
#include "timer/timer.h"



/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int disable = 0;
int iLed = 0;
int numClienti = 0;
void RIT_IRQHandler (void)
{					
	static int left=0, right=0, down=0, up=0, select=0;
	static int debounce=0, debounce1=0, debounce2=0;	
	
	//GESTIONE DEBOUNCE BOTTONI
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0 && disable == 0){ /*BOTTONE PREMUTO*/
		debounce1++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ 	
			reset_RIT();
			enable_timer(0);
			switch(debounce1){
				case 1: 
					S += 1;
					iLed = 7;
					LED_On(iLed);
					enable_timer(0);
					disable = 1;
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce1=0;			
			//disable_RIT();
			//reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
		}
		
	}  	

	if((LPC_PINCON->PINSEL4 & (1 << 24)) == 0 && disable == 0){ /*BOTTONE PREMUTO*/
		debounce2++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){ 	
			reset_RIT();
			enable_timer(0);
			switch(debounce2){
				case 1: 
					N += 1;
					iLed = 6;
					LED_On(iLed);
					enable_timer(0);
					disable = 1;
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else{	/* button released */
			debounce2=0;			
			//disable_RIT();
			//reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* esco da modalita' GPIO*/
		}
		
	}  	
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0 && disable == 0){ /*BOTTONE PREMUTO*/
		debounce++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ 	
			reset_RIT();
			enable_timer(0);
			switch(debounce){
				case 1: 
					I += 1;
					iLed = 5;
					LED_On(iLed);
					enable_timer(0);
					disable = 1;
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else{	/* button released */
			debounce=0;			
			//disable_RIT(); //Da commentare se gestisco anche joystick, in tutti i bottoni
			//reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* esco da modalita' GPIO*/
		}
		
	}  	
	
	
	
	//GESTIONE JOYSTICK 
	
	//UP=29, RIGHT=28, LEFT=27, DOWN=26
	if ((LPC_GPIO1->FIOPIN & (1 << 29)) == 0) { // JOYSTICK UP
				// AZIONE UP
		up++;	
		
				
	
		
		if(up!=0) {
			
		}
		
		up=0;
	}


	if ((LPC_GPIO1->FIOPIN & (1 << 28)) == 0 && disable == 0) { // JOYSTICK RIGHT
				// AZIONE RIGHT
		right++;
		if(right != 0){
			numClienti = stat_satisfaction(S, N, I, &pS, &pN, &pI);
			LED_Out(numClienti);
			disable = 1;
			enable_timer(1);
		}
	} 
	else {
		right=0;
	}


	if ((LPC_GPIO1->FIOPIN & (1 << 27)) == 0 && disable == 0) { // JOYSTICK LEFT
				// AZIONE LEFT
		left++;
		if(left!=0) {
			pS = 0;
			pI = 0;
			pN = 0;
			S = 0;
			N = 0;
			I = 0;
		}
		left=0;
	}


	if ((LPC_GPIO1->FIOPIN & (1 << 26)) == 0 ) { // JOYSTICK DOWN
				// AZIONE DOWN
		down++;
	} 
	else {
		down=0;
	}


	if((LPC_GPIO1->FIOPIN & (1 << 25)) == 0 ){ // SELECT (R3,L3)
			// AZIONE SELECT
		
		select++;

	}
	else  {
		select=0;
	}

	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File

******************************************************************************/
