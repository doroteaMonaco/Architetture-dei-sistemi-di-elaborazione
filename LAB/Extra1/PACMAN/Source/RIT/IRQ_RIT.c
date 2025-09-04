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
#include "GLCD.h"
#include "button.h"


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int flag = 0;



void RIT_IRQHandler (void)
{					
	static int position = 0; //1:Up, 2:DOWN, 3:LEFT, 4:RIGHT
	static int debounce = 0;
	scorePrecedente = score;
	
	
	
	reset_RIT();
	if(victory==0) return;
	



	if (i_ghost==i_start && j_ghost==j_start && power==1 && flagm!=-1) { //se pacman sta attaccando il fantasma e l'ha raggiunto
		score+=100; //aumento score
		secondspawn=count-3; //aspetto 3s per respawnare fantasma
		flagm=-1; //metto flag per non far spawnare fantasma
	}
	
	if (i_ghost==i_start && j_ghost==j_start && power==0) { //se fantasma sta attaccando pacman e l'ha raggiunto
		cancellaCella(i_start,j_start);
		i_start=10;
		j_start=13;
		disegnaPacmanRight(i_start,j_start); //disegno pacman in cella iniziale
		dead=1; //flag morte
		cancellaPacmanLife(i_life,j_life);
		i_life-=3; //coordinata vita disegnata
							current_lives_remaining--;
		

		
		if(i_life<0) { //non ho più vite
			victory=0;
			disable_timer(1);
			disable_RIT();			// stoppo il gioco
				LCD_Clear(Black);
				GUI_Text(6*10+10, 12*10+40, (uint8_t *) " Game Over! ", Red, Black);
		}
		
	}
	if(dead == 1){
		position = -1;
	}
	if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ 
		if(debounce == 0){
			debounce = 1;
			if(pause == 0){
				pause = 1;
				disable_timer(1);
				disable_timer(2);
				GUI_Text(9*10+11, 12*10+32, (uint8_t *) "PAUSE", Yellow, Blue);
			}
			else{
				pause = 0;
				enable_timer(1);
				enable_timer(2);
				GUI_Text(9*10+11, 12*10+32, (uint8_t *) "     ", Blue, Blue);
				cancellaPacman(10, 11);
				cancellaPacman(10, 12);

				cancellaPacman(11, 11);
				cancellaPacman(11, 12);
				cancellaPacman(12, 11);
				cancellaPacman(12, 12);
				
				cancellaPacman(9, 11);
				cancellaPacman(9, 12);
				
				displaySquare(9,11);
				displaySquare(9,12);
				displaySquare(10,12);
				displaySquare(11,12);
				displaySquare(12,12);
				displaySquare(12,11);
				
				displaySquare(12,11);	
			}
		}
	}
	else {	/* button released */
		debounce=0;			
		NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	}
	
	if(pause == 0){
		if((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && position != 1){	
			/* Joytick UP pressed */
			position = 1;
			if(flag == 0){
				enable_timer(1);
				flag = 1;
			}
			if(position == 1){
				if(schermo[i_start][j_start-1] != -1){ //è una casella vuota
					cancellaPacman(i_start, j_start);
					score += schermo[i_start][j_start-1];
					disegnaPacmanUp(i_start, j_start-1);
					
					j_start -= 1;
					
					PutChar(152, 20, (score/1000)%10+48, White, Black);
					PutChar(160, 20, (score/100)%10+48, White, Black);
					PutChar(168, 20, (score/10)%10+48, White, Black);
					PutChar(176, 20, score%10+48, White, Black);
				}
				else{ //muro
					cancellaPacman(i_start, j_start);
					disegnaPacmanUp(i_start, j_start);
				}
				
				if(scorePrecedente % 1000 > score % 1000 && scorePrecedente != score){
					i_life += 3;
					disegnaPacmanLife(i_life, j_life);
					current_lives_remaining++;
				}
			}
			return;
		}
		
		if((LPC_GPIO1->FIOPIN & (1<<26)) == 0 && position != 2){	
		/* Joytick DOWN pressed */
			position = 2;
			if(flag == 0){
				enable_timer(1);
				flag = 1;
			}

			if(position == 2){
				if(schermo[i_start][j_start+1] != -1){ //è una casella vuota
					cancellaPacman(i_start, j_start);
					score += schermo[i_start][j_start+1];
					disegnaPacmanDown(i_start, j_start+1);
					
					j_start += 1;
					
					PutChar(152, 20, (score/1000)%10+48, White, Black);
					PutChar(160, 20, (score/100)%10+48, White, Black);
					PutChar(168, 20, (score/10)%10+48, White, Black);
					PutChar(176, 20, score%10+48, White, Black);
				}
				else{ //muro
					cancellaPacman(i_start, j_start);
					disegnaPacmanUp(i_start, j_start);
				}
				if(scorePrecedente % 1000 > score % 1000 && scorePrecedente != score){
					i_life += 3;
					disegnaPacmanLife(i_life, j_life);
					current_lives_remaining++;
				}
			}
			return;
		}
		
		if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && position != 3){	
		/* Joytick LEFT pressed */
			position = 3;
			if(flag == 0){
				enable_timer(1);
				flag = 1;
			}
			
			if(i_start == 0){
				cancellaPacman(i_start, j_start);
				i_start = 22;
			}
			
			if(position == 3){
				if(schermo[i_start-1][j_start] != -1){ //è una casella vuota
					if(i_start != 22){
						cancellaPacman(i_start, j_start);
					}
					score += schermo[i_start-1][j_start];
					
					i_start -= 1;
					disegnaPacmanLeft(i_start, j_start);
					
					PutChar(152, 20, (score/1000)%10+48, White, Black);
					PutChar(160, 20, (score/100)%10+48, White, Black);
					PutChar(168, 20, (score/10)%10+48, White, Black);
					PutChar(176, 20, score%10+48, White, Black);
				}
				else{ //muro
					cancellaPacman(i_start, j_start);
					disegnaPacmanLeft(i_start, j_start);
				}
				
				if(scorePrecedente % 1000 > score % 1000 && scorePrecedente != score){
					i_life += 3;
					disegnaPacmanLife(i_life, j_life);
					current_lives_remaining++;
				}
			}
			return;
		}
		
		if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && position != 4){	
		/* Joytick RIGHT pressed */
			position = 4;
			if(flag == 0){
				enable_timer(1);
				flag = 1;
			}
			
			if(i_start == 21){
				cancellaPacman(i_start, j_start);
				i_start = -1;
			}
			
			if(position == 4){
				if(schermo[i_start+1][j_start] != -1){ //è una casella vuota
					if(i_start != -1){
						cancellaPacman(i_start, j_start);
					}
					score += schermo[i_start+1][j_start];
					disegnaPacmanRight(i_start+1, j_start);
					
					i_start += 1;
					
					PutChar(152, 20, (score/1000)%10+48, White, Black);
					PutChar(160, 20, (score/100)%10+48, White, Black);
					PutChar(168, 20, (score/10)%10+48, White, Black);
					PutChar(176, 20, score%10+48, White, Black);
				}
				else{ //muro
					cancellaPacman(i_start, j_start);
					disegnaPacmanRight(i_start, j_start);
				}
				
				if(scorePrecedente % 1000 > score % 1000 && scorePrecedente != score){
					i_life += 3;
					disegnaPacmanLife(i_life, j_life);
					current_lives_remaining++;
				}
			}
			return;
		}
		if(pause==0 && dead==0) {
		
	
		if(position==1) { //UP
			if(schermo[i_start][j_start-1]!=-1) { //non è un muro
				score+=schermo[i_start][j_start-1];
			if(schermo[i_start][j_start-1]>0) {
					countPillar--;
					
				}
				cancellaPacman(i_start, j_start); //cancello pacman nella vecchia casella
				
				disegnaPacmanUp(i_start, j_start-1);
				j_start-=1;
				
				PutChar(160,20,(score/100)%10+48,White,Black);
				PutChar(168,20,(score/10)%10+48,White,Black);
				PutChar(152,20,(score/1000)%10+48,White,Black);
				PutChar(176,20,score%10+48,White,Black);
				
				
				if(score!=0 && scorePrecedente%1000>score%1000 && score!=scorePrecedente) {
					i_life+=3;
					disegnaPacmanLife(i_life,j_life);
										current_lives_remaining++;

				}
				
				
			}
			
			else { //se è un muro disegno pacman up
				cancellaPacman(i_start, j_start);
				disegnaPacmanUp(i_start, j_start);
				
			}
			
		}
		
		
		if(position==2) { //RIGHT
			if (i_start==21) {
			cancellaPacman(i_start, j_start);
			i_start=-1;
			
		}
			if(schermo[i_start+1][j_start]!=-1) { //non è un muro
				score+=schermo[i_start+1][j_start];
			if(schermo[i_start+1][j_start]>0) {
					countPillar--;
					
				}
				if(i_start!=-1) {
					cancellaPacman(i_start, j_start); //cancello pacman nella vecchia casella
					
				}
				
			
					i_start+=1;

					disegnaPacmanRight(i_start, j_start);

				
				
				PutChar(160,20,(score/100)%10+48,White,Black);
				PutChar(168,20,(score/10)%10+48,White,Black);
				PutChar(152,20,(score/1000)%10+48,White,Black);
				PutChar(176,20,score%10+48,White,Black);
				
				if(score!=0 && scorePrecedente%1000>score%1000 && score!=scorePrecedente) {
					i_life+=3;
					disegnaPacmanLife(i_life,j_life);
										current_lives_remaining++;

				}
				
			}
			
			else { //se è un muro disegno pacman right
				cancellaPacman(i_start, j_start);
				disegnaPacmanRight(i_start, j_start);
				
			}
			
		}
	
		
		if(position==3) { //LEFT
			if (i_start==0) {
				cancellaPacman(i_start, j_start);
				i_start=22;
			
			}
			if(schermo[i_start-1][j_start]!=-1) { //non è un muro
				score+=schermo[i_start-1][j_start];
			if(schermo[i_start-1][j_start]>0) {
					countPillar--;
					
				}
				if (i_start!=22) {
					cancellaPacman(i_start, j_start); //cancello pacman nella vecchia casella

				}
				
				
				
				i_start-=1;

				disegnaPacmanLeft(i_start, j_start);
				
				PutChar(160,20,(score/100)%10+48,White,Black);
				PutChar(168,20,(score/10)%10+48,White,Black);
				PutChar(152,20,(score/1000)%10+48,White,Black);
				PutChar(176,20,score%10+48,White,Black);
				
				
				if(score!=0 && scorePrecedente%1000>score%1000 && score!=scorePrecedente) {
					i_life+=3;
					disegnaPacmanLife(i_life,j_life);
										current_lives_remaining++;

				}
			}
			
			else { //se è un muro disegno pacman left
				cancellaPacman(i_start, j_start);
				disegnaPacmanLeft(i_start, j_start);
				
			}
			
		}
		
		
		if(position==4) { //DOWN
			if(schermo[i_start][j_start+1]!=-1) { //non è un muro
				score+=schermo[i_start][j_start+1];
			if(schermo[i_start][j_start+1]>0) {
					countPillar--;
					
				}
				cancellaPacman(i_start, j_start); //cancello pacman nella vecchia casella
				
				disegnaPacmanDown(i_start, j_start+1);
				j_start+=1;
				
				PutChar(160,20,(score/100)%10+48,White,Black);
				PutChar(168,20,(score/10)%10+48,White,Black);
				PutChar(152,20,(score/1000)%10+48,White,Black);
				PutChar(176,20,score%10+48,White,Black);
				
				if(score!=0 && scorePrecedente%1000>score%1000 && score!=scorePrecedente) {
					i_life+=3;
					disegnaPacmanLife(i_life,j_life);
										current_lives_remaining++;

				}
				
			}
			
			else { //se è un muro disegno pacman down
				cancellaPacman(i_start, j_start);
				disegnaPacmanDown(i_start, j_start);
				
			}
			
		}
	
	
		
	}
	
	
	

	}
	
	if(dead==1) { //se entro essendo morto pulisco flag
		dead=0;
	}
		
	
	reset_RIT();
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
                              End Of File
******************************************************************************/
