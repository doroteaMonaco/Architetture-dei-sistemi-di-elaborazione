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
#include "led/led.h"

#define N 10
#define M 14
#define BOUNDARY 2


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
int c=0;
int discard=0; //conto values scartati

void RIT_IRQHandler (void)
{					
	static int position=-1; //1->UP, 2->RIGHT, 3->LEFT, 4->DOWN	
	static int debounce=0;	
	static int value, i=0; //value e offset vett
	static int flag=0; //flag per abilitare key 
	
	//GESTIONE DEBOUNCE BOTTONI
	debounce++;
	
	
	
	//INT0=10, KEY1==11, KEY2=12
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0) {
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ /*BOTTONE PREMUTO*/		
			reset_RIT();
			switch(debounce){
				case 1: /*dopo INTERVALLO RIT (es.50ms) faccio azione*/
					//FAI AZIONE
					if(first==1) { //la prima volta che premo key1 
						first=0;
						discard=0; //porto i discard a 0
						enable_timer(2); //abilito timer 2 per prendere TC
						disable_timer(0); //disabilito timer0
						reset_timer(0);
					}
					else {
						disable_timer(2); 
						value = LPC_TIM2->TC; //lettura di TC di timer2
						enable_timer(2);
						value=ExtractVal(value); //estraggo value
						if(check_fibonacci(&vett[i], N, M, value, BOUNDARY)==1) { //se value accettabile
							i++; //aumento offset vett
							flag=1; //setto flag che IMPEDISCE al RIT di abilitare interrupt key1 (lo voglio disabilitato fino al termine dei 2s->timer1)
							
							if(i==10) { //quando ho riempito tutto vett
								clean_vett(); //pulisco vett
								LED_Out(discard); //mostro values scartati
								enable_timer(0); //abilito timer0 per lampeggio led discard
								i=0; //offset vett a 0 per successiva iterazione
								disable_timer(2); //disabilito timer2 
								reset_timer(2);
								first=1;	//la prossima iterazione è la prima 
							}
							
							NVIC_DisableIRQ(EINT1_IRQn);		/* disabilito interrupr key1 (verrà abilitata al termine dei 2s)			 */
							LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */

							
							LED_Out(0xFF); //led accesi
							disable_timer(1); //disabilito timer1 così posso riabilitarlo (altrimenti rimane STOPPATO anche se riscrivo enable)
							reset_timer(1);
							enable_timer(1); //riabilito timer1 (era STOP e INTERRUPT), qui lo riabilito
							enable_timer(3); //abilito timer3 per lampeggio led value
							c++;
						}
						else { //se value non accettabile
							LED_Out(0xFF); //led accesi fissi
							discard++; //aumento scartati
							
						}
					}
						
					
						
						

						
					
					
					break;
				default: /*altrimenti il bottone è premuto per più tempo e non faccio nulla*/
					break;
			}
		}
		else {	/* button released */
			debounce=0;			
			disable_RIT();
			reset_RIT();
			//INT0=20 e EINT0_IRQn, KEY1==22 e EINT1_IRQn, KEY2=24 e EINT2_IRQn
			if(flag==0) { //riattivo interrupt key1 solo se non l'ho disabilitato prima (periodo 2s in cui è disattivo)
				NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
			
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
				
			}
			else { //se ho disabilitato prima interrupt key1 non voglio che venga riabilitato qui (ma lo faccio in timer1)
				flag=0; //rimetto flag a 0 così nella successiva iterazione al rientro del periodo di 2s l'interrupt verrà riattivato dal RIT
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
