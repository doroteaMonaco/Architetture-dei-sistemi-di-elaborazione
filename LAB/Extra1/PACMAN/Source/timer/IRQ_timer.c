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
#include "GLCD.h"
#include <stdint.h>
#include <AsciiLib.h>
#include <RIT/RIT.h>
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
unsigned char ledval = 0xA5;
int pillarsRemained = 6;
int count = 60;
int flagm=1;
int victory=2;
int offset = 0;
int offsetgh = 0;
int secondpower = 0;
int speed = 0;



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
	unsigned int p, s;
	
	
	if(LPC_TIM1->IR & 1) // MR0
	{
		if(offset==4) { //ogni 4 volte entro decremento secondi di 1 (così ho margine per muovere i fantasmi più veloce)
			p=(count/10);
			s=(count%10);
			
			offset=0;
			
						
			PutChar(48,20,p+48,White,Black);
			PutChar(57,20,s+48,White,Black);
			PutChar(66,20,115,White,Black);
			

			count--;
			if(count==40) { //modalità di velocità 1
				speed=1;
			}
			else if(count==20) { //modalità di velocità 2
				speed=2;
			}
			if(count==secondpower) { //dopo 10s finishe frightned mode
				power=0;
				
			}
			if(count==secondspawn) { //dopo 3s respawna fantasma
				i_ghost=10;
				j_ghost=10;
				disegnaFantasma(i_ghost,j_ghost,Blue);
				secondspawn=-1;
				flagm=1;
				
			}
			if (count==0) { //allo scadere del tempo perdo
				victory=0;
				disable_timer(1);
				PutChar(48,20,48,White,Black);
				PutChar(57,20,48,White,Black);
				PutChar(66,20,115,White,Black);
				//GAMEOVER
				
				disable_RIT();			// stoppo il gioco
				disable_timer(1);
				LCD_Clear(Black);
				GUI_Text(6*10+10, 12*10+40, (uint8_t *) " Game Over! ", Red, Black);
				

				
				
				
				
				
				
			}	
				
			}
		if(speed==0 && flagm>=1) { //modalità velocità iniziale
			if(offsetgh>=4) { //muovo fantasma ogni 1s
				offsetgh=0;
				moveGhost();
			}
		}
		else if(speed==1 && flagm>=1) { //modalità velocità 1
			if(offsetgh>=2) { //muovo fantasma ogni 0.5s
				offsetgh=0;
				moveGhost();
			}
		}
		else if(speed==2 && flagm>=1) { //modalità velocità 2
			if(offsetgh>=1) { //muovo fantasma ogni 0.125s
				offsetgh=0;
				moveGhost();
			}
		}
		offset++;
		offsetgh++;
		
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
	if(LPC_TIM2->IR & 1) // MR0
	{
		int i_rand, j_rand;
		if(pillarsRemained != 0){
			i_rand = (LPC_TIM0->TC)%DIM;
			j_rand = (LPC_TIM1->TC)%DIM;
			for(; schermo[i_rand][j_rand] != 10; i_rand = rand() % DIM, j_rand = rand() % DIM); 
			disegnaPillarM(i_rand, j_rand);
			pillarsRemained--;
		}
		else{
			disable_timer(2);
		}
		LPC_TIM2->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM2->IR & 2){ // MR1
		disable_timer(0); // duration della nota
		LPC_TIM2->IR = 2;			// clear interrupt flag 
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