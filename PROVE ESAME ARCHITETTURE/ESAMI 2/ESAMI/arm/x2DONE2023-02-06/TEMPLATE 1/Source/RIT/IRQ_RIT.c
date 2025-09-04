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
#define N 8

int i=0, mod=0,s;
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
int extractbits(uint32_t* v);

void RIT_IRQHandler (void)
{					
	static int up=0, left=0, down=0; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce=0,sec,msec, k;	
	static unsigned int sum;
	static char al;
	static uint32_t dis;
	
	//GESTIONE DEBOUNCE BOTTONI
	
	
	
	//INT0=10, KEY1==11, KEY2=12
	//INT0=20, KEY1==22, KEY2=24
	if(mod==0) {
			if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){ /*BOTTONE PREMUTO*/
			debounce++;
			if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ 	
				reset_RIT();
				switch(debounce){
					case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
						enable_timer(0);
						break;
					default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
						break;
				}
			}
			else {	/* button released */
				debounce=0;			
				//disable_RIT();
				//reset_RIT();
				//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
				sec=counters*50/1000; 
				msec=counters*50%1000;
				disable_timer(1);
				reset_timer(1);
				c=0;
				if(sec<2) {
					VAR1+=2;
					dis=VAR1;
					if(dis<=15) {
						for(k=4;k<8;k++) {
							if(extractbits(&dis)==0) {
								LED_Off(k);
							}
							else {
								LED_On(k);
							}
						}
					}
					else {
						for(k=4;k<8;k++) {
							LED_On(k);
						}
						enable_timer(1);
					}
					
				}
				else if(sec==2 || (sec==3 && msec==0)) {
					VAR1+=3;
					dis=VAR1;
					if(dis<=15) {
						for(k=4;k<8;k++) {
							if(extractbits(&dis)==0) {
								LED_Off(k);
							}
							else {
								LED_On(k);
							}
						}
					}
					else {
						for(k=4;k<8;k++) {
							LED_On(k);
						}
						enable_timer(1);
					}
				}
				else {
					disable_timer(1);
					reset_timer(1);
					sum=calcola_somma_prodotto(VETT, N, &al);
					VAR1=0;
					VAR2=0;
					clear_vett();
					mod=1;
					i=0;
					if(al==1) {
							LED_Out(0xFF);
							enable_timer(2);
						}
						else {
							LED_Out(sum);
						}
					
				}
				counters=0;
				disable_timer(0);
				reset_timer(0);
				NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
				
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
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
					VAR2+=1;
					disable_timer(3);
					reset_timer(3);
					c=3;
					dis=VAR2;
						if(dis<=15) {
							for(k=0;k<4;k++) {
								if(extractbits(&dis)==0) {
									LED_Off(k);
								}
								else {
									LED_On(k);
								}
							}
						}
						else {
							for(k=0;k<4;k++) {
								LED_On(k);
							}
							enable_timer(3);
						}
					
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
					VAR2+=1;
				disable_timer(3);
					reset_timer(3);
					c3=1;
					dis=VAR2;
						if(dis<=15) {
							for(k=0;k<4;k++) {
								if(extractbits(&dis)==0) {
									LED_Off(k);
								}
								else {
									LED_On(k);
								}
							}
						}
						else {
							for(k=0;k<4;k++) {
								LED_On(k);
							}
							enable_timer(3);
						}
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
					VETT[i]=VAR1;
					i++;
					VETT[i]=VAR2;
					i++;
					if(i==N) {
						disable_timer(1);
						reset_timer(1);
						sum=calcola_somma_prodotto(VETT, N, &al);
						s=sum;
						i=0;
						VAR1=0;
						VAR2=0;
						clear_vett();
						mod=1;
						if(al==1) {
							LED_Out(0xFF);
							enable_timer(2);
						}
						else {
							LED_Out(sum);
						}
					}
				
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
			
			
			
		}
		else {
			down=0;
			
		}
	}
	
	
	
	
		
	
	

	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File

******************************************************************************/
