#include "button.h"
#include "LPC17xx.h"
#include "timer/timer.h"
#include "RIT/RIT.h"


//extern unsigned char next_state(unsigned char current_state, unsigned char taps, int *output_bit);
//volatile unsigned char current_state=0xAA;
//volatile unsigned char taps = 0b00111001;
int first=1;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	
	//LED_On(0);
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	NVIC_EnableIRQ(EINT2_IRQn);							 /* RIATTIVO interruzione*/
			
	LPC_PINCON->PINSEL4    |= (1 << 24);     /* esco da modalita' GPIO*/
	if (first==1) {
		first=0;
		enable_timer(2);
	}
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	//LED_Out(current_state);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	
	
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


