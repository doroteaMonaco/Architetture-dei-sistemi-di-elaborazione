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
int ready = 0;
int negOdd = 0;
int counter = 0;
int on = 0;

void RIT_IRQHandler (void)
{					
	static int left=0, right=0, down=0, up=0, select=0;
	static int debounce=0, debounce1=0, debounce2=0;	
	
	//GESTIONE DEBOUNCE BOTTONI
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){ /*BOTTONE PREMUTO*/
		debounce1++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ 	
			reset_RIT();
			switch(debounce1){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce1=0;			
//			disable_RIT();
//			reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
		}
		
	}  	

	if((LPC_PINCON->PINSEL4 & (1 << 24)) == 0){ /*BOTTONE PREMUTO*/
		debounce2++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){ 	
			reset_RIT();
			switch(debounce2){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce2=0;			
//			disable_RIT();
//			reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* esco da modalita' GPIO*/
		}
		
	}  	
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){ /*BOTTONE PREMUTO*/
		debounce++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ 	
			reset_RIT();
			switch(debounce){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce=0;			
//			disable_RIT(); //Da commentare se gestisco anche joystick, in tutti i bottoni
//			reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* esco da modalita' GPIO*/
		}
		
	}  	
	
	
	
	//GESTIONE JOYSTICK 
	
	//UP=29, RIGHT=28, LEFT=27, DOWN=26
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	// UP PREMUTO
		up++;
		reset_RIT();
		switch(up){
			case 1: 
				VAR1 += 12;
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
	}
	else {	/* button released */
		up = 0;
	}

	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){ // RIGHT PREMUTO
		right++;
		reset_RIT();
		switch(right){
			case 1:
				ready = 1;
				vett[index] = VAR1;
				index++;
				VAR1 = 0;
				if(index == N){
					counter = 0;
					disable_timer(0);
					reset_timer(0);
					negOdd = count_negative_and_odd(vett, N);
					if(negOdd == 0){
						LED_On(7);
						enable_timer(0);
					}
					else{
						LED_Off(7);
						int i;
						for(i=0; i<7; i++){
							if(negOdd & (1<<i)){
								LED_On(i);
							}
							else{
								LED_Off(i);
							}
						}
					}
					
					index = 0;
				}
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
	}
	else {	/* button released */
		right = 0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0) { // LEFT PREMUTO
		left++;
		reset_RIT();
		switch(left){
			case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
				//FAI AZIONE
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
	}
	else {	/* button released */
		left = 0;
	}
		
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0) { // DOWN PREMUTO
		down++;
		reset_RIT();
		switch(down){
			case 1: 
				VAR1 -= 8;
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
	}
	else {	/* button released */
		down = 0;
	}
	if ((LPC_GPIO1->FIOPIN & (1<<25)) == 0) { // SELECT PREMUTO
		select++;
		reset_RIT();
		switch(select){
			case 1: 
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
	}
	else {	/* button released */
		select = 0;
	}

	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File

******************************************************************************/
