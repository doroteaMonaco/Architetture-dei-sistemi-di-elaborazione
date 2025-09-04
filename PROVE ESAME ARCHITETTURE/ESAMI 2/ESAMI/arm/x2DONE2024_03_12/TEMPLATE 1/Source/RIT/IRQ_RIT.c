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
#define N 4
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

unsigned char ExtractBits(int value);
unsigned char get_and_sort(unsigned char* v, unsigned char va, int n);
int indexled;
int disable=0;
void RIT_IRQHandler (void)
{					
	static int up=0, left=0, down=0, value; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce=0;	
	
	
	//GESTIONE DEBOUNCE BOTTONI
	
	
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	
		if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){ /*BOTTONE PREMUTO*/
		debounce++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ 	
			reset_RIT();
			switch(debounce){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					disable_timer(1); 
					value = LPC_TIM1->TC; //lettura di TC 
					enable_timer(1);
					VAL=ExtractBits(value);
					VETT[index]=VAL;
					LED_Out(index+1);
					index++;
					VAL=get_and_sort(VETT, VAL, index);
				
					if(index==N) {
						index=0;
						indexled=index;
						
						enable_timer(2);
						NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
						LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
						disable=1;
	
					}
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce=0;			
			disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			reset_RIT(); //da COMMENTARE se gestisco anche joystick
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			if(disable==0) {
				NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
			
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
			}
			
		}
		
	}  	

	
	
	
	//GESTIONE JOYSTICK 
	
	//UP=29, RIGHT=28, LEFT=27, DOWN=26
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	// UP PREMUTO
		up++;
		//GESTIONE BOTTONE PREMUTO
		reset_RIT();
		switch(up){
			case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
				//FAI AZIONE
				
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
		
		
		
	}
	else {
		up=0;
		
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	// LEFT PREMUTO
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
	else {
		left=0;
		
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	// DOWN PREMUTO
		down++;
		reset_RIT();
		switch(down){
			case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
				//FAI AZIONE
			
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
		
		
		
	}
	else {
		down=0;
		
	}
	
	
	
	
	
		
	
	

	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File

******************************************************************************/
