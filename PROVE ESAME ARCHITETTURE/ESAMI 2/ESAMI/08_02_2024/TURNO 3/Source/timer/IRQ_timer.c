/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"
#include "RIT/RIT.h"
#include "led/led.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern volatile unsigned char led_value;					/* defined in funct_led								*/

uint32_t val_TC; 
int counter0=0, end=0, counter1=0, counterfine=0;
unsigned int compare (unsigned char* V, unsigned char* V1, const unsigned int n);
void TIMER0_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		if(end==0) {
			if(counter0%2==0) {
				LED_Out(0x0);
			}
			else {
				LED_Out(0xFF);
			}
			counter0++;
			if(counter0==5) {
				counter0=0;
				disable_timer(0);
				reset_timer(0);
				disabilitato=0;
				index++;
				if(index==N) {
						end=1;
						disable_timer(0);
						reset_timer(0);
						enable_timer(0);
						LED_On(1);
						LED_On(2);

						disabilitato=1;
					}
				while(VETT[index]!=1 && VETT[index]!=2 && index<N) {
					index++;
					if(index==N) {
						end=1;
						disable_timer(0);
						reset_timer(0);
						enable_timer(0);
						LED_On(1);
						LED_On(2);

						disabilitato=1;
						break;
					}
				}
				if(index<N) {
						LED_On(VETT[index]);

				}
				
			}
		}
		else {
			if(counter1%2==0) {
				LED_Off(1);
				LED_Off(2);
			}
			else {
				LED_On(1);
				LED_On(2);
			}
			counter1++;
			if(counter1==9) {
				counter1=0;
				disable_timer(0);
				reset_timer(0);
				LED_Out(0xFF);
				enable_timer(1);
				
			}
		}
		
			
		
		
		LPC_TIM0->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM0->IR & 2){ // MR1
		// your code	
		LPC_TIM0->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 4){ // MR2
		// your code	
		LPC_TIM0->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 8){ // MR3
		// your code	
		LPC_TIM0->IR = 8;			// clear interrupt flag 
	}
  return;
}

/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void) 
{
	static int cmp;
	if(counterfine%2==0) {
				LED_Out(0x00);
			}
			else {
				LED_Out(0xFF);
			}
			counterfine++;
			if(counterfine==25) {
				counterfine=0;
				disable_timer(1);
				reset_timer(1);
				cmp=compare (VETT, VETT2, N);
				LED_Out(cmp);
				fine=1;
				
				
			}
	
	
	
	if(LPC_TIM1->IR & 1) // MR0
	{ 

		
			LPC_TIM1->IR = 1;			//clear interrupt flag

		}

	else if(LPC_TIM1->IR & 2){ // MR1
		//LED_Out(ledval);
		LPC_TIM1->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM1->IR & 4){ // MR2
		// your code	
		LPC_TIM1->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM1->IR & 8){ // MR3
		// your code	
		LPC_TIM1->IR = 8;			// clear interrupt flag 
	} 

	return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
// gestisce il debounce di INT0
void TIMER2_IRQHandler (void)
{
	if(LPC_TIM2->IR & 1) // MR0 
	{ 
		LPC_TIM2->IR = 1;			//clear interrupt flag
	}
	
	/*else if(LPC_TIM2->IR & 2){ // MR1
		// your code	
		LPC_TIM2->IR = 2;			// clear interrupt flag 
	}*/
	return;
}


/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
  if(LPC_TIM3->IR & 1) // MR0
	{ 
		//LED_Off(1);
		LPC_TIM3->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM3->IR & 2){ // MR1
		//LED_On(1);
		LPC_TIM3->IR = 2;			// clear interrupt flag 
	}
	
  //LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

/*
void TIMER0_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		// your code
		LPC_TIM0->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM0->IR & 2){ // MR1
		// your code	
		LPC_TIM0->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 4){ // MR2
		// your code	
		LPC_TIM0->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 8){ // MR3
		// your code	
		LPC_TIM0->IR = 8;			// clear interrupt flag 
	}
  return;
}*/