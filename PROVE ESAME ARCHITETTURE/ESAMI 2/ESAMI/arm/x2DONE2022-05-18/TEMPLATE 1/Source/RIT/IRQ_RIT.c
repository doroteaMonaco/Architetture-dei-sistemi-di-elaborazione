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
#define MAX 80
#define MIN 20
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
uint8_t VAR;
unsigned char VETT[100];
int index=0, countbyte=0, disable=0;
unsigned int tpcf;
void clear_vett();
unsigned int totale_pressioni_con_filtro(unsigned char* v, unsigned int i, unsigned char ma, unsigned char mi);
unsigned char ExtractByte(unsigned int* t);
int key1=0, int0=0, key2=0;
void RIT_IRQHandler (void)
{					
	static int up=0, left=0, down=0; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce=0, debounce2=0,sec, debounce0=0;
	static unsigned char dis;
	
	
	
	//GESTIONE DEBOUNCE BOTTONI
	
	
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	
		if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){ /*BOTTONE PREMUTO*/
		debounce++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ 	
			reset_RIT();
			switch(debounce){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					key1++;
					enable_timer(0);
					disable_timer(1);
					reset_timer(1);
					count1=0;
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			key1=key1+10;
			debounce=0;			
			disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			reset_RIT(); //da COMMENTARE se gestisco anche joystick
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			disable_timer(0);
			reset_timer(0);
			if(countds<=255) {
				VAR=countds;
				LED_Out(VAR);
				
			}
			else {
				VAR=255;
				LED_Out(VAR);
				
				enable_timer(1);
			}
			
			
			countds=0;
			
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
					key2++;
					enable_timer(0);
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			key2=key2+10;
			debounce2=0;			
			disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			reset_RIT(); //da COMMENTARE se gestisco anche joystick
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			disable_timer(0);
			reset_timer(0);
			sec=countds/10+countds%10;
			if(sec<1) {
				VETT[index]=VAR;
				index++;
				if(index==100) {
					tpcf=totale_pressioni_con_filtro(VETT, index, MAX, MIN);
					index=0;
					dis=ExtractByte(&tpcf);
					LED_Out(dis);
					enable_timer(2);
					NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
					//LPC_PINCON->PINSEL4    &= ~(1 << 24);
					
					NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
					//LPC_PINCON->PINSEL4    &= ~(1 << 22); 

					NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
					//LPC_PINCON->PINSEL4    &= ~(1 << 20); 
					
					disable=1;
					
					
				}
				
			}
			else {
				clear_vett();
				index=0;
				
			}
			
			
			countds=0;
			
			if(disable==0) {
				NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
				LPC_PINCON->PINSEL4    |= (1 << 24);  /* esco da modalita' GPIO*/
			}
			    
		}
		
	}  	
	
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){ /*BOTTONE PREMUTO*/
		debounce0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ 	
			reset_RIT();
			switch(debounce0){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					int0++;
					tpcf=totale_pressioni_con_filtro(VETT, index, MAX, MIN);
					index=0;
					dis=ExtractByte(&tpcf);
					LED_Out(dis);
					enable_timer(2);
					NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
					//LPC_PINCON->PINSEL4    &= ~(1 << 24);
					
					NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
					//LPC_PINCON->PINSEL4    &= ~(1 << 22);  
				
				  NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
					//LPC_PINCON->PINSEL4    &= ~(1 << 20); 
					
					disable=1;
					
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce0=0;			
			int0=int0+10;
			disable_RIT(); //da COMMENTARE se gestisco anche joystick (nel rit non entro solo premendo il joystick, infatti enable_RIT() va messo anche nel main
			reset_RIT(); //da COMMENTARE se gestisco anche joystick
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			
			
			if(disable==0) {
				NVIC_EnableIRQ(EINT0_IRQn);							 /* RIATTIVO interruzione*/
			
				LPC_PINCON->PINSEL4    |= (1 << 20); 
			}
				 /* esco da modalita' GPIO*/
			
			    
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
