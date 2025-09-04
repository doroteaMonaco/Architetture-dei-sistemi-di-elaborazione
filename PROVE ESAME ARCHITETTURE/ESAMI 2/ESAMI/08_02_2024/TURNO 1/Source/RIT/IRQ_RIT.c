/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
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
unsigned char led07, led07inv;
uint32_t value=0;
int flag=0,key1=0,key2=0;

void RIT_IRQHandler (void)
{					
	static int position=-1; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce1=0;	
	static int debounce2=0;
	
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
					enable_timer(0); //inizio a contare cs
					key1++;
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce1=0;			
			disable_RIT();
			reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			if(flag==0) {
				NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
			
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
			}
			
		}
		
	}  
	
	
	if((LPC_PINCON->PINSEL4 & (1 << 24)) == 0 && first==0){ /*BOTTONE PREMUTO*/
			debounce2++;

		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){ 	
			reset_RIT();
			switch(debounce2){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					lampeggio=1;
					value=cs;
					cs=0;
					disable_timer(0);
					reset_timer(0);
					key2++;
				
					led07=extractbyte(value);
					led07inv=extractopposite(led07);
				
					enable_timer(1); //stampo led07 e led07inv
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce2=0;			
			disable_RIT();
			reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			//if(flag==0) {
				//NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
				//LPC_PINCON->PINSEL4    |= (1 << 24);     /* esco da modalita' GPIO*/
			//}
		
			
		}
		
	}  	

		

	
	
	
	//GESTIONE JOYSTICK 
	
	//UP=29, RIGHT=28, LEFT=27, DOWN=26
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	// UP PREMUTO
		position=1;
		//GESTIONE BOTTONE PREMUTO
		
		
		
	}
	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){ // RIGHT PREMUTO
		position=2;

	}
	else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0) { // LEFT PREMUTO
		position=3;
		
	}
	
	else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0) { // DOWN PREMUTO
		position=4;
		
	}
	else if ((LPC_GPIO1->FIOPIN & (1<<25)) == 0) { // SELECT PREMUTO
		position=4;
		
	}
	
	switch(position) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
	}
		
	
	

	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File

******************************************************************************/
