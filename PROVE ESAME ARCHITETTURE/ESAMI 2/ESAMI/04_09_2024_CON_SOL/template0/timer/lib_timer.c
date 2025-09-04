/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
	switch(timer_num){
		case 0:
			LPC_TIM0->TCR=1;
			break;
		case 1:
			LPC_TIM1->TCR=1;
			break;
		case 2:
			LPC_TIM2->TCR=1;
			break;
		case 3:
			LPC_TIM3->TCR=1;
			break;
		default:
			break;
	}
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  switch(timer_num){
		case 0:
			LPC_TIM0->TCR=0;
			break;
		case 1:
			LPC_TIM1->TCR=0;
			break;
		case 2:
			LPC_TIM2->TCR=0;
			break;
		case 3:
			LPC_TIM3->TCR=0;
			break;
		default:
			break;
	}
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  switch(timer_num){
		case 0:
			LPC_TIM0->TCR |= (1<<1); //bit 1 is then put to 0 when the timer start
			break;
		case 1:
			LPC_TIM1->TCR |= (1<<1);
			break;
		case 2:
			LPC_TIM2->TCR |= (1<<1);
			break;
		case 3:
			LPC_TIM3->TCR |= (1<<1);
			break;
		default:
			break;
	}
  return;
}



uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval, uint8_t match_reg_num, uint16_t SRI_value)
{
	uint32_t check=0;
	
	if(SRI_value>7){
		SRI_value=3; // Default Value, do Reset and Interrupt
	}
	
	switch(timer_num){
	//+++++++++++++++ TIMER 0 +++++++++++++++++++++
		case 0:
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM0->MR0=TimerInterval;
					LPC_TIM0->MCR|=SRI_value;  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM0->MR1=TimerInterval;
					LPC_TIM0->MCR|=(SRI_value<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM0->MR2=TimerInterval;
					LPC_TIM0->MCR|=(SRI_value<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM0->MR3=TimerInterval;
					LPC_TIM0->MCR|=(SRI_value<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER0_IRQn);
			NVIC_SetPriority(TIMER0_IRQn,0);
			break;
	//++++++++++++++++ TIMER 1 ++++++++++++++++++++++++++++
		case 1:
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM1->MR0=TimerInterval;
					LPC_TIM1->MCR|=SRI_value;  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM1->MR1=TimerInterval;
					LPC_TIM1->MCR|=(SRI_value<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM1->MR2=TimerInterval;
					LPC_TIM1->MCR|=(SRI_value<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM1->MR3=TimerInterval;
					LPC_TIM1->MCR|=(SRI_value<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER1_IRQn);
			NVIC_SetPriority(TIMER1_IRQn,1);
			break;
	//+++++++++++++++++ TIMER 2 +++++++++++++++++++++++++++++
		case 2:
			LPC_SC->PCONP|=(1<<22);
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM2->MR0=TimerInterval;
					LPC_TIM2->MCR|=SRI_value;  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM2->MR1=TimerInterval;
					LPC_TIM2->MCR|=(SRI_value<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM2->MR2=TimerInterval;
					LPC_TIM2->MCR|=(SRI_value<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM2->MR3=TimerInterval;
					LPC_TIM2->MCR|=(SRI_value<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER2_IRQn);
			NVIC_SetPriority(TIMER2_IRQn,2);
			break;
	//++++++++++++++++ TIMER 3 +++++++++++++++++++++++++++
		case 3:
			LPC_SC->PCONP|=(1<<23);
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM3->MR0=TimerInterval;
					LPC_TIM3->MCR|=SRI_value;  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM3->MR1=TimerInterval;
					LPC_TIM3->MCR|=(SRI_value<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM3->MR2=TimerInterval;
					LPC_TIM3->MCR|=(SRI_value<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM3->MR3=TimerInterval;
					LPC_TIM3->MCR|=(SRI_value<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER3_IRQn);
			NVIC_SetPriority(TIMER3_IRQn,3);
			break;
		default:
			break;
	}
	return check;
}




/*

uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval, uint8_t match_reg_num)
{
	uint32_t check=0;
	switch(timer_num){
	//+++++++++++++++ TIMER 0 +++++++++++++++++++++
		case 0:
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM0->MR0=TimerInterval;
					LPC_TIM0->MCR|=(0<<2)|(1<<1)|(1<<0);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM0->MR1=TimerInterval;
					LPC_TIM0->MCR|=(0<<5)|(1<<4)|(1<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM0->MR2=TimerInterval;
					LPC_TIM0->MCR|=(0<<8)|(1<<7)|(1<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM0->MR3=TimerInterval;
					LPC_TIM0->MCR|=(0<<11)|(1<<10)|(1<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER0_IRQn);
			NVIC_SetPriority(TIMER0_IRQn,0);
			break;
	//++++++++++++++++ TIMER 1 ++++++++++++++++++++++++++++
		case 1:
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM1->MR0=TimerInterval;
					LPC_TIM1->MCR|=(0<<2)|(1<<1)|(1<<0);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM1->MR1=TimerInterval;
					LPC_TIM1->MCR|=(0<<5)|(1<<4)|(1<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM1->MR2=TimerInterval;
					LPC_TIM1->MCR|=(0<<8)|(1<<7)|(1<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM1->MR3=TimerInterval;
					LPC_TIM1->MCR|=(0<<11)|(1<<10)|(1<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER1_IRQn);
			NVIC_SetPriority(TIMER1_IRQn,1);
			break;
	//+++++++++++++++++ TIMER 2 +++++++++++++++++++++++++++++
		case 2:
			LPC_SC->PCONP|=(1<<22);
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM2->MR0=TimerInterval;
					LPC_TIM2->MCR|=(0<<2)|(1<<1)|(1<<0);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM2->MR1=TimerInterval;
					LPC_TIM2->MCR|=(0<<5)|(1<<4)|(1<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM2->MR2=TimerInterval;
					LPC_TIM2->MCR|=(0<<8)|(1<<7)|(1<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM2->MR3=TimerInterval;
					LPC_TIM2->MCR|=(0<<11)|(1<<10)|(1<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER2_IRQn);
			NVIC_SetPriority(TIMER2_IRQn,2);
			break;
	//++++++++++++++++ TIMER 3 +++++++++++++++++++++++++++
		case 3:
			LPC_SC->PCONP|=(1<<23);
			switch(match_reg_num){
				case 0:
					//++++ MR0 ++++++
					LPC_TIM3->MR0=TimerInterval;
					LPC_TIM3->MCR|=(0<<2)|(1<<1)|(1<<0);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 1:
					//++++ MR1 ++++++
					LPC_TIM3->MR1=TimerInterval;
					LPC_TIM3->MCR|=(0<<5)|(1<<4)|(1<<3);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 2:
					//++++ MR2 ++++++
					LPC_TIM3->MR2=TimerInterval;
					LPC_TIM3->MCR|=(0<<8)|(1<<7)|(1<<6);  //Stop-Reset-Interrupt
					check=1;
					break;
				case 3:
					//++++ MR3 ++++++
					LPC_TIM3->MR3=TimerInterval;
					LPC_TIM3->MCR|=(0<<11)|(1<<10)|(1<<9);  //Stop-Reset-Interrupt
					check=1;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER3_IRQn);
			NVIC_SetPriority(TIMER3_IRQn,3);
			break;
		default:
			break;
	}
	return check;
}

*/

int timer_getValue(uint8_t timer_num){
	int var=0;
	switch(timer_num){
		case 0:
			disable_timer(0);
			var=LPC_TIM0->TC;
			enable_timer(0);
			break;
		case 1:
			disable_timer(1);
			var=LPC_TIM1->TC;
			enable_timer(1);
			break;
		case 2:
			disable_timer(2);
			var=LPC_TIM2->TC;
			enable_timer(2);
			break;
		case 3:
			disable_timer(3);
			var=LPC_TIM3->TC;
			enable_timer(3);
			break;
		default:
			break;
	}
	return var;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
