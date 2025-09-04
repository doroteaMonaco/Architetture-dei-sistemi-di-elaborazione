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
#define N 4
unsigned char VETT2[N];
char RES[N];
unsigned char analisi_accuratezza(unsigned char *vett, unsigned char *vett2, int N1, char *res);
unsigned char acc;
int match, score;

void RIT_IRQHandler (void)
{					
	static int position=-1; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce=0, value, ds;	
	
	//GESTIONE DEBOUNCE BOTTONI
	
	debounce++;
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){ /*BOTTONE PREMUTO*/
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ 	
			reset_RIT();
			switch(debounce){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					value=VETT[i];
					match=value;
					LED_Out(value);
					enable_timer(0);
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce=0;			
			disable_RIT();
			reset_RIT();
			LED_Out(0x0);
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			disable_timer(0);
			reset_timer(0);
			ds=count*50/100 + count*50%100;
			score=ds;
			VETT2[i]=ds;
			count=0;
			
			i++;
			
			if(i==N) {
				acc=analisi_accuratezza(VETT, VETT2, N, RES);
				i=0;
				if(RES[i]>acc) {
					LED_Out(RES[i]);
					enable_timer(1);
				}
				else {
					enable_timer(2);
				}
				
			}
			else {
				NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
			
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
				
				
			}
			
			
			
			
			
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
