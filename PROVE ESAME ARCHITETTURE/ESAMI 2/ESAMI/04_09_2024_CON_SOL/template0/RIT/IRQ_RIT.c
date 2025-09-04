/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../adc/adc.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down0=0;
volatile int down1=0;	
volatile int down2=0;


#define N 8

unsigned int VAR=0;
unsigned int VETT[N]={0};

int n=0;
char flag;
int count_more_than_avg;
char neg_value;

unsigned int avg_vett(unsigned int VETT[], unsigned int dim, char* flag);

void RIT_IRQHandler (void)
{			
	static int joy_sel=0;
	static int joy_down=0;
	static int joy_up=0;
	static int joy_left=0;
	static int joy_right=0;
	//++++++++++++++++++++++++++++++++++++++++++
	//								BUTTONS
	//++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++ KEY 0 ++++++++++++++++++++++
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){
		if(down0>1){
			if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){   //int0
				switch(down0){
					case 2:
						//+++++++ PRIMA PRESSIONE ++++++++++++
					
						disable_timer(1); // per non rischiare di far sovrascrivere VAR dal timer1 durante queste azioni
					
						if(n==0 || (VETT[n-1]!=VAR) ){
							VETT[n]=VAR;
							n++;
							
							if(n==N){
								count_more_than_avg = avg_vett(VETT, n, &flag);
													
								//clean previous result
								disable_timer(0);
								reset_timer(0);
								LED_Out(0);
								
								n=0;
								
								if(flag==0){
									neg_value = count_more_than_avg & 0x000000FF;
									
									LED_Out_Neg(neg_value);
								}
								else{
									LED_On_Board(6);
									enable_timer(0);
								}
							}								
						}
						enable_timer(1);
					
						break;
					default:
						break;
				}
				down0++;
			}
			else {	/* button released */
				down0=0;			
				NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
			}
		}else{
			down0++;
		}
	}	
	
	//++++++++++++++ KEY 1 +++++++++++++++++++
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){	//check for GPIO mode
		if(down1>1){
			if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){   //key1
				switch(down1){
					case 2:
						//+++++++ PRIMA PRESSIONE ++++++++++++
						
						break;
					default:
						break;
				}
				down1++;
			}
			else {	/* button released */
				down1=0;			
				NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
			}
		}else{
			down1++;
		}
	}			
	//++++++++++++++ KEY 2 +++++++++++++++++++
	if((LPC_PINCON->PINSEL4 & (1 << 24)) == 0){	//check for GPIO mode
		if(down2>1){
			if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){   //key1
				switch(down2){
					case 2:
						//+++++++ PRIMA PRESSIONE ++++++++++++
						
						break;
					default:
						break;
				}
				down2++;
			}
			else {	/* button released */
				down2=0;			
				NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
			}
		}else{
			down2++;
		}
	}	
	//+++++++++++++++++++++++++++++++++++++++++++++
	//									JOYSTICK										
	//+++++++++++++++++++++++++++++++++++++++++++++
	
	//+++++++++ SEL ++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
		joy_sel++;
		switch(joy_sel){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				break;
			default:
				break;
		}
	}else{
		joy_sel=0;
	}
	
	
	//+++++++++ DOWN ++++++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){
		joy_down++;
		switch(joy_down){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				break;
			default:
				break;
		}
	}else{
		joy_down=0;
	}
	
	
	//+++++++++ LEFT ++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
		joy_left++;
		switch(joy_left){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				break;
			default:
				break;
		}
	}else{
		joy_left=0;
	}
	
	
	//+++++++++ RIGHT ++++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
		joy_right++;
		switch(joy_right){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				break;
			default:
				break;
		}
	}else{
		joy_right=0;
	}
	
	
	//+++++++++ UP ++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){
		joy_up++;
		switch(joy_up){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				break;
			default:
				break;
		}
	}else{
		joy_up=0;
	}
	
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
