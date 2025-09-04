#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

extern unsigned char next_state(unsigned char current_state, unsigned char taps, int *output_bit);
volatile unsigned char current_state = 0xAA;
volatile unsigned char taps = 0x1;
int output_bit = 0;

void EINT0_IRQHandler (void)	  
{
	LED_On(0);
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	LED_Out(0);
	current_state = next_state(current_state, taps, &output_bit);
	LED_Out(current_state);
	
	LPC_SC->EXTINT &= (1 << 1);    /*clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	LED_Out(0);
	volatile unsigned char initial_state = current_state;
	current_state = next_state(initial_state, taps, &output_bit);
	volatile int count = 1;
	while(current_state != initial_state){
		current_state = next_state(current_state, taps, &output_bit);
		count++;
	}
	LED_Out(count);

  LPC_SC->EXTINT &= (1 << 2);     /*clear pending interrupt         */    
}


