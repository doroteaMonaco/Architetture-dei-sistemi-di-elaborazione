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
int count_negative_and_odd(int* v,int n);
void RIT_IRQHandler (void)
{					
	static int up=0, left=0, down=0, right=0, select=0; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce0=0, debounce1=0, debounce2=0, count_negative;	
	
	
	//GESTIONE DEBOUNCE BOTTONI
	
	
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){ /*BOTTONE PREMUTO*/
		debounce0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ 	
			reset_RIT();
			switch(debounce0){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce0=0;			
			disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			reset_RIT(); //da COMMENTARE se gestisco anche joystick
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* esco da modalita' GPIO*/
		}
		
	}  	
	
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
			disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			reset_RIT(); //da COMMENTARE se gestisco anche joystick
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
			disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			reset_RIT(); //da COMMENTARE se gestisco anche joystick
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* esco da modalita' GPIO*/
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
				VAR1+=10;
				
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
		
		
		
	}
	else {
		up=0;
		
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	// RIGHT PREMUTO
		right++;
		reset_RIT();
		switch(right){
			case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
				//FAI AZIONE
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
		
		
		
	}
	else {
		right=0;
		
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
				VAR1-=8;
			
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
		
		
		
	}
	else {
		down=0;
		
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	// SELECT PREMUTO
		select++;
		reset_RIT();
		switch(select){
			case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
				//FAI AZIONE
				VETT[index]=VAR1;
				VAR1=0;
				index++;
				if(index==N) {
					count_negative=count_negative_and_odd(VETT,N);
					if(count_negative==0) {
						LED_On(0);
						enable_timer(0);
						flagon=1;
					}
					else {
						count_negative=count_negative<<1;
						LED_Out(count_negative);
					}
					index=0;
				}
			
				break;
			default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
				break;
		}
		
		
		
	}
	else {
		select=0;
		
	}
	
	
	

	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File

******************************************************************************/
