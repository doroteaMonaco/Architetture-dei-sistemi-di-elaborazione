/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"
#include "../adc/adc.h"
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/

#define N 8

extern unsigned int VAR;
extern unsigned int VETT[N];


int toggle=1;

void TIMER0_IRQHandler (void)
{
	/*
	  if (LPC_TIM0->IR & (1 << 0)) {  // MR0 ha generato l'interrupt
    }
    else if (LPC_TIM0->IR & (1 << 1)) {  // MR1 ha generato l'interrupt
    }
    else if (LPC_TIM0->IR & (1 << 2)) {  // MR2 ha generato l'interrupt
    }
		else if (LPC_TIM0->IR & (1 << 3)) {  // MR3 ha generato l'interrupt
    }
	*/	
		
	if(toggle){
		LED_Off_Board(6);
		toggle=0;
	}
	else{
		LED_On_Board(6);
		toggle=1;
	}
  
	LPC_TIM0->IR |= ((1<<3)|(1<<2)|(1<<1)|(1<<0));			/* clear interrupt flag MR3-MR2-MR1-MR0*/
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
	VAR = timer_getValue(2);
	
  LPC_TIM1->IR = ((1<<3)|(1<<2)|(1<<1)|(1<<0));			/* clear interrupt flag MR3-MR2-MR1-MR0*/
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = ((1<<3)|(1<<2)|(1<<1)|(1<<0));			/* clear interrupt flag MR3-MR2-MR1-MR0*/
  return;
}

/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
  LPC_TIM3->IR = ((1<<3)|(1<<2)|(1<<1)|(1<<0));			/* clear interrupt flag MR3-MR2-MR1-MR0*/
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
