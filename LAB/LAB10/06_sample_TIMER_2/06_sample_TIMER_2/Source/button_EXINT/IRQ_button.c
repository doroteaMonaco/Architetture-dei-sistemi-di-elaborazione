#include "button.h"
#include "LPC17xx.h"
#include <stdint.h>

#include "../led/led.h"
#include "../timer/timer.h"

#define N 7000
extern void bubble_sort(uint32_t *v, char c, int dim);
extern uint32_t v[N];
uint32_t copia[N];
int i=0;
float media = 0.0;


void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	disable_timer(1);
	for(i=0; i<N; i++){
		bubble_sort(copia,v[i],i);
	}
	enable_timer(1);
	
	for(i=0; i<N; i++){
		media += (float) copia[i];
		
		copia[i] = 0xCAFECAFE;
	}
	
	media = media/N;
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */  
	enable_timer(0);  
}


