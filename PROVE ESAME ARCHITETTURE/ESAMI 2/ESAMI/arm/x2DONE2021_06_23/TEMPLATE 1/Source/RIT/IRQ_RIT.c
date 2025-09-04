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
unsigned int sopra_la_media(unsigned char* V,int i);
int disattivato=0;

void RIT_IRQHandler (void)
{					
	static int up=0, left=0, down=0, right=0, select=0; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce0=0, debounce1=0, debounce2=0, sup_media=0;	
	
	
	//GESTIONE DEBOUNCE BOTTONI
	
	
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0 && disattivato==0){ /*BOTTONE PREMUTO*/
		debounce0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ 	
			reset_RIT();
			switch(debounce0){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					VETT[index]=VAR;
					VAR=0;
					index++;
					if(index>=2 && index<N) {
						if(VETT[index-1]==VETT[index-2]) {
							sup_media=sopra_la_media(VETT,index);
							disattivato=1;
							if (sup_media>=0 && sup_media<=255) {
								LED_Out(sup_media);
							}
							LED_Out(0xAA);
							enable_timer(1);
						}
					}
					else if(index==N) {
						sup_media=sopra_la_media(VETT,index);
						disattivato=1;
						if (sup_media>=0 && sup_media<=255) {
								LED_Out(sup_media);
							}
						LED_Out(0xAA);
						enable_timer(1);
					}
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce0=0;			
			//disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			//reset_RIT(); //da COMMENTARE se gestisco anche joystick
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
			//disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			//reset_RIT(); //da COMMENTARE se gestisco anche joystick
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
			//disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			//reset_RIT(); //da COMMENTARE se gestisco anche joystick
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* esco da modalita' GPIO*/
		}
		
	}  	
  	

	
	
	
	//GESTIONE JOYSTICK 
	
	//UP=29, RIGHT=28, LEFT=27, DOWN=26
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && disattivato==0){	// UP PREMUTO
		up++;
		//GESTIONE BOTTONE PREMUTO
		reset_RIT();
		
		enable_timer(0);
				
				
		
		
		
	}
	else if (left==0 && select==0){
		up=0;
		disable_timer(0);
		reset_timer(0);
		VAR+=counter0;
		if(VAR<=255 && VAR>=0) {
			LED_Out(VAR);
		}
		else if (VAR>255) {
			LED_Out(255);
		}
		else {
			LED_Out(0x0);
		}
		counter0=0;
		
		
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
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && disattivato==0){	// LEFT PREMUTO
		left++;
		reset_RIT();
		
		enable_timer(0);
				
		
		
		
	}
	else if(up==0 && select==0) {
		left=0;
		disable_timer(0);
		reset_timer(0);
		VAR-=counter0;
		if(VAR>=0 && VAR<=255) {
			LED_Out(VAR);
		}
		else if(VAR>255) {
			LED_Out(255);
		}
		else {
			LED_Out(0x0);
		}
		counter0=0;
		
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
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0 && disattivato==0){	// SELECT PREMUTO
		select++;
		reset_RIT();
		
				VAR=0;
				LED_Out(VAR);
				
		
		
		
	}
	else if((LPC_GPIO1->FIOPIN & (1<<25)) == 0 && disattivato==1) {
		disattivato=0;
		VAR=0;
		clear_vett();
		index=0;
		disable_timer(1);
		reset_timer(1);
		counter1=0;
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
