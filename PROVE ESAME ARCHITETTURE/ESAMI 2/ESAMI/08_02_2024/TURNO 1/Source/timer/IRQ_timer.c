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
#define N 6

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
int lampeggio=1,t1=0,t2=0,t0=0,t3=0, NU;

uint32_t val_TC; 


void TIMER0_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		t0++;
		cs++;
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
void TIMER1_IRQHandler (void) //GESTIONE COUNTER 60 SECONDI
{
	
	
	
	if(LPC_TIM1->IR & 1) // MR0
	{ 

		if(lampeggio%2==0) {
			LED_Out(led07inv);
			
		}	
		else {
			LED_Out(led07);
		}
		lampeggio++;
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

void TIMER2_IRQHandler (void)
{
	static unsigned char num;
	if(LPC_TIM2->IR & 1) // MR0 -> lavoro con MR0 per il debounce
	{ 
		
		vett[i]=value;
		i++;
		if(i==6) {
			flag=1;
			NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
			LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
			
			NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
			LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
			
			
			disable_timer(1);
			reset_timer(1);
			num=contatore_inrange(vett, N);
			t2++;
			NU=num;
			LED_Out(num);
			
			enable_timer(3); //cancello num
			i=0;
			disable_timer(2);
			reset_timer(2);
			
			
		}
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
		LED_Out(0x0);
		clear_vett();
		value=0;
		flag=0;
		
		NVIC_EnableIRQ(EINT1_IRQn);							 /* RIATTIVO interruzione*/
			
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* esco da modalita' GPIO*/
		
		
		NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* esco da modalita' GPIO*/
		
		first=1;
		disable_timer(3);
		reset_timer(3);
		
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