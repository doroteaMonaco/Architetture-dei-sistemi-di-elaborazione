/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"



#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

void displaySquare(int i, int j);
void cancellaCella(int i, int j);
void inizializzazioneSchermo();
void disegnaForma(int i, int j, char tipo);
void disegnaPacmanLeft(int i, int j);
void disegnaPacmanRight(int i, int j);
void disegnaPacmanUp(int i, int j);
void disegnaPacmanDown(int i, int j);
void cancellaPacman(int i, int j);
void inizializzaPillars();
void disegnaPillarS(int i, int j);
void disegnaPillarM(int i, int j);
void disegnaPacmanLife(int i, int j);
void cancellaPacmanLife(int i, int j);
void disegnaFantasma(int i, int j, int color);
void cancellaFantsma(int i, int j);
void startGhost();
void moveGhost();


#define DIM 22
int countPillar = 0;
int schermo[DIM][DIM];
int i_start = 1;
int j_start = 1;
int score = 0;
int i_life = 0;
int j_life = 23;
int scorePrecedente = 0;
int debounce_active = 0;
int pause;
int i_ghost = 10;
int j_ghost = 10;
int power = 0;
int secondspawn = -1;
int current_lives_remaining = 1;
int dead=0; 

void disegnaFantasma(int i, int j, int colore){
		int x = i*10+10;
	  int y = j*10+40;
	  if(schermo[i][j] == -1)
			return;
		//corpo
		LCD_DrawLine(x+2, y, x+7, y, colore);	
		LCD_DrawLine(x+1, y+1, x+8, y+1, colore);	
		LCD_DrawLine(x, y+2, x, y+7, colore);	
		LCD_DrawLine(x+9, y+2, x+9, y+7, colore);	
		LCD_DrawLine(x+8, y+4, x+9, y+4, colore);	
		LCD_DrawLine(x+1, y+2, x+1, y+2, colore);	
		LCD_DrawLine(x+8, y+2, x+8, y+2, colore);	
		LCD_DrawLine(x+3, y+2, x+6, y+2, colore);	
		LCD_DrawLine(x+4, y+3, x+5, y+3, colore);
	  LCD_DrawLine(x+3, y+4, x+6, y+4, colore);	
		LCD_DrawLine(x, y+4, x+1, y+4, colore);
		LCD_DrawLine(x, y+5, x+9, y+5, colore);
		LCD_DrawLine(x, y+6, x+9, y+6, colore);
		LCD_DrawLine(x, y+7, x+9, y+7, colore);
		LCD_DrawLine(x+1, y+8, x+1, y+9, colore);
		LCD_DrawLine(x+3, y+8, x+3, y+9, colore);
		LCD_DrawLine(x+6, y+8, x+6, y+9, colore);
		LCD_DrawLine(x+8, y+8, x+8, y+9, colore);
		
		//occhi
		LCD_DrawLine(x+1, y+3, x+3, y+3, White);
		LCD_DrawLine(x+2, y+2, x+2, y+4, White);
		LCD_DrawLine(x+6, y+3, x+8, y+3, White);
		LCD_DrawLine(x+7, y+2, x+7, y+4, White);

		LCD_DrawLine(x+2, y+3, x+2, y+3, Black);
		LCD_DrawLine(x+7, y+3, x+7, y+3, Black);
		return;
}

void cancellaFantasma(int i, int j){
	if(i >= DIM || j >= DIM) return;
	int x = i*10+10, y = j*10+40,k;
	
	
	for(k=0;k<10;k++) {
		LCD_DrawLine(x,y+k,x+9,y+k,Black);

	}
	
	if(schermo[i][j] == 10)
		disegnaPillarS(i, j);
	else if(schermo[i][j] == 50)
		disegnaPillarM(i, j);
	return;
}

void startGhost() {
	LCD_DrawLine(10*10+10,10*10+35,12*10+9,10*10+35,Black);
	schermo[10][9]=0;
	schermo[11][9]=0;
}

void moveGhost() {
	
	
	
	if(secondspawn==-1) {
		cancellaFantasma(i_ghost,j_ghost);

	

	if(power==0 ) { //FANTASMA ATTACCA
		
		
		if(schermo[i_ghost][j_ghost]==10) {
		disegnaPillarS(i_ghost,j_ghost);
	}
	else if(schermo[i_ghost][j_ghost]==50) {
		disegnaPillarM(i_ghost,j_ghost);
	}
	if(i_start>i_ghost && schermo[i_ghost+1][j_ghost]!=-1 && i_ghost+1<DIM) {
		i_ghost++;
	}
	else if(i_start<i_ghost && schermo[i_ghost-1][j_ghost]!=-1 && i_ghost-1>=0) {
		i_ghost--;
	}
	else if(j_start>j_ghost && schermo[i_ghost][j_ghost+1]!=-1 && j_ghost+1<DIM) {
		j_ghost++;
	}
	else if(j_start<j_ghost && schermo[i_ghost][j_ghost-1]!=-1 && j_ghost-1>=0) {
		j_ghost--;
	}
	else if(schermo[i_ghost+1][j_ghost]!=-1 && i_ghost+1<DIM) {
		i_ghost++;
	}
	else if(schermo[i_ghost-1][j_ghost]!=-1 && i_ghost-1>=0) {
		i_ghost--;
	}
	else if(schermo[i_ghost][j_ghost+1]!=-1 && j_ghost+1<DIM) {
		j_ghost++;
	}
	else if(schermo[i_ghost][j_ghost-1]!=-1 && j_ghost-1>=0) {
		j_ghost--;
	}
	
	
		disegnaFantasma(i_ghost,j_ghost,Red);

	
		
	}
	
	else { //PACMAN ATTACCA
		int i_target, j_target;
		
		
		if (i_start>=10) {
			i_target=1;
		}
		else {
			i_target=20;
		}
		
		if (j_start>=10) {
			j_target=1;
		}
		else {
			j_target=20;
		}
		
		if(schermo[i_ghost][j_ghost]==10) {
		disegnaPillarS(i_ghost,j_ghost);
	}
	else if(schermo[i_ghost][j_ghost]==50) {
		disegnaPillarM(i_ghost,j_ghost);
	}
	if(i_target>i_ghost && schermo[i_ghost+1][j_ghost]!=-1 && i_ghost+1<DIM) {
		i_ghost++;
	}
	else if(i_target<i_ghost && schermo[i_ghost-1][j_ghost]!=-1 && i_ghost-1>=0) {
		i_ghost--;
	}
	else if(j_target>j_ghost && schermo[i_ghost][j_ghost+1]!=-1 && j_ghost+1<DIM) {
		j_ghost++;
	}
	else if(j_target<j_ghost && schermo[i_ghost][j_ghost-1]!=-1 && j_ghost-1>=0) {
		j_ghost--;
	}
	else if(schermo[i_ghost+1][j_ghost]!=-1 && i_ghost+1<DIM) {
		i_ghost++;
	}
	else if(schermo[i_ghost-1][j_ghost]!=-1 && i_ghost-1>=0) {
		i_ghost--;
	}
	else if(schermo[i_ghost][j_ghost+1]!=-1 && j_ghost+1<DIM) {
		j_ghost++;
	}
	else if(schermo[i_ghost][j_ghost-1]!=-1 && j_ghost-1>=0) {
		j_ghost--;
	}
	
	
				
			disegnaFantasma(i_ghost,j_ghost,Blue);
		

		
	
	
	
	
	}
	
	}
	

	


}

void cancellaPacman(int i, int j){
	if(i >= DIM || j >= DIM) return;
	int x = i*10+10, y = j*10+40;
	LCD_DrawLine(x, y, x+9, y, Black);
	LCD_DrawLine(x, y+1, x+9, y+1, Black);
	LCD_DrawLine(x, y+2, x+9, y+2, Black);
	LCD_DrawLine(x, y+3, x+9, y+3, Black);
	LCD_DrawLine(x, y+4, x+9, y+4, Black);
	LCD_DrawLine(x, y+5, x+9, y+5, Black);
	LCD_DrawLine(x, y+6, x+9, y+6, Black);
	LCD_DrawLine(x, y+7, x+9, y+7, Black);
	LCD_DrawLine(x, y+8, x+9, y+8, Black);
	LCD_DrawLine(x, y+9, x+9, y+9, Black);
	
	if(schermo[i][j]==50) {
		power=1;
		secondpower=count-10;
	}
	
	schermo[i][j] = 0;
	
	return;
}



void disegnaPacmanLife(int i, int j){
    int x = i * 10 + 10; // Offset laterale per schermo
    int y = j * 10 + 40; // Offset verticale per schermo

    // Disegno scalato: ogni coordinata moltiplicata per 4
	
	
		LCD_DrawLine(x+3, y+1, x+14, y+1, Yellow);

		LCD_DrawLine(x+2, y+2, x+15, y+2, Yellow);
		LCD_DrawLine(x+2, y+3, x+15, y+3, Yellow);
	
		LCD_DrawLine(x+1, y+4, x+17, y+4, Yellow);
		LCD_DrawLine(x+1, y+5, x+17, y+5, Yellow);
	
		LCD_DrawLine(x+4, y+6, x+18, y+6, Yellow);
		LCD_DrawLine(x+4, y+7, x+18, y+7, Yellow);
	
		LCD_DrawLine(x+9, y+8, x+18, y+8, Yellow);
		LCD_DrawLine(x+9, y+9, x+18, y+9, Yellow);
	
		LCD_DrawLine(x+13, y+10, x+18, y+10, Yellow);
		LCD_DrawLine(x+13, y+11, x+18, y+11, Yellow);
		
		LCD_DrawLine(x+9, y+12, x+18, y+12, Yellow);
		LCD_DrawLine(x+9, y+13, x+18, y+13, Yellow);
		
		LCD_DrawLine(x+4, y+14, x+18, y+14, Yellow);
		LCD_DrawLine(x+4, y+15, x+18, y+15, Yellow);
		
		LCD_DrawLine(x+1, y+16, x+17, y+16, Yellow);
		LCD_DrawLine(x+1, y+17, x+17, y+17, Yellow);
		
		LCD_DrawLine(x+2, y+18, x+15, y+18, Yellow);
		LCD_DrawLine(x+2, y+19, x+15, y+19, Yellow);
		
		LCD_DrawLine(x+3, y+20, x+14, y+20, Yellow);
		
		
		return;
}

void cancellaPacmanLife(int i, int j){
    int x = i * 10 + 10; // Offset laterale per schermo
    int y = j * 10 + 40; // Offset verticale per schermo

	
	
		LCD_DrawLine(x+3, y+1, x+14, y+1, Black);

		LCD_DrawLine(x+2, y+2, x+15, y+2, Black);
		LCD_DrawLine(x+2, y+3, x+15, y+3, Black);
	
		LCD_DrawLine(x+1, y+4, x+17, y+4, Black);
		LCD_DrawLine(x+1, y+5, x+17, y+5, Black);
	
		LCD_DrawLine(x+4, y+6, x+18, y+6, Black);
		LCD_DrawLine(x+4, y+7, x+18, y+7, Black);
	
		LCD_DrawLine(x+9, y+8, x+18, y+8, Black);
		LCD_DrawLine(x+9, y+9, x+18, y+9, Black);
	
		LCD_DrawLine(x+13, y+10, x+18, y+10, Black);
		LCD_DrawLine(x+13, y+11, x+18, y+11, Black);
		
		LCD_DrawLine(x+9, y+12, x+18, y+12, Black);
		LCD_DrawLine(x+9, y+13, x+18, y+13, Black);
		
		LCD_DrawLine(x+4, y+14, x+18, y+14, Black);
		LCD_DrawLine(x+4, y+15, x+18, y+15, Black);
		
		LCD_DrawLine(x+1, y+16, x+17, y+16, Black);
		LCD_DrawLine(x+1, y+17, x+17, y+17, Black);
		
		LCD_DrawLine(x+2, y+18, x+15, y+18, Black);
		LCD_DrawLine(x+2, y+19, x+15, y+19, Black);
		
		LCD_DrawLine(x+3, y+20, x+14, y+20, Black);
		
		
		return;
	
}
void displaySquare(int i, int j){
	if(schermo[i][j] == -1) return; 
	
	int x = i*10+10;
	int y = j*10+40;

	
	LCD_DrawLine(x, y, x+9, y, Yellow);
	LCD_DrawLine(x, y, x, y+9, Yellow);
	LCD_DrawLine(x, y+9, x+9, y+9, Yellow);
	LCD_DrawLine(x+9, y, x+9, y+9, Yellow);
	
	schermo[i][j] = -1;
	
	return;
}


void disegnaForma(int i, int j, char tipo){
	
	switch(tipo){
		case 'a': //quadrato semplice
			displaySquare(i, j);
			break;
		case 'b': //forma T
			displaySquare(i, j);
			displaySquare(i+1, j);
			displaySquare(i+2, j);
			displaySquare(i+1, j+1);
			break;
		case 'c': //forma pollice
			displaySquare(i, j);
			displaySquare(i, j+1);
			displaySquare(i, j+2);
			displaySquare(i-1, j+1);
			displaySquare(i-1, j+2);
			break;
		case 'd': //forma pistola
			displaySquare(i, j);
			displaySquare(i, j+1);
			displaySquare(i, j+2);
			displaySquare(i, j+3);
			displaySquare(i, j+4);
			displaySquare(i+1, j+2);
			displaySquare(i+1, j+3);
			break;
		case 'e': //forma assalto
			displaySquare(i, j);
			displaySquare(i, j+1);
			displaySquare(i, j+2);
			displaySquare(i, j+3);
			displaySquare(i, j+4);
			displaySquare(i, j+5);
			displaySquare(i+1, j+5);
			displaySquare(i-1, j+2);
			break;
		case 'f': //forma castello
			displaySquare(i, j);
			displaySquare(i, j+1);
			displaySquare(i+1, j+1);
			displaySquare(i+2, j+1);
			displaySquare(i+3, j+1);
			displaySquare(i+4, j+1);
			displaySquare(i+4, j);
			break;
		case 'g': //forma linea
			displaySquare(i, j);
			displaySquare(i, j+2);
			displaySquare(i, j+3);
			displaySquare(i, j+5);
			break;
		case 'h': //forma angolo
			displaySquare(i, j);
			displaySquare(i, j+1);
			displaySquare(i+1, j);
			break;
	}
	return;
}

void disegnaPacmanLeft(int i, int j){ // coordinate fittizie della mia matrice 20x20
	if(i >= DIM || j >= DIM) return;
	int x = i*10+10, y = j*10+40;					// pixel effettivi con offset (laterale e verticale per avere bene lo schermo)
	LCD_DrawLine(x+3, y, x+6, y, Yellow);
	LCD_DrawLine(x+2, y+1, x+7, y+1, Yellow);
	LCD_DrawLine(x+1, y+2, x+8, y+2, Yellow);
	LCD_DrawLine(x+2, y+3, x+9, y+3, Yellow);
	LCD_DrawLine(x+4, y+4, x+9, y+4, Yellow);
	LCD_DrawLine(x+6, y+5, x+9, y+5, Yellow);
	LCD_DrawLine(x+4, y+6, x+9, y+6, Yellow);
	LCD_DrawLine(x+2, y+7, x+9, y+7, Yellow);
	LCD_DrawLine(x+1, y+8, x+8, y+8, Yellow);
	LCD_DrawLine(x+2, y+9, x+7, y+9, Yellow);
	return;
}

void disegnaPacmanRight(int i, int j){ // coordinate fittizie della matrice 20x20
	if(i >= DIM || j >= DIM) return;
	int x = i*10+10, y = j*10+40; // pixel effettivi con offset (laterale e verticale per avere bene lo schermo)
	LCD_DrawLine(x+4, y, x+7, y, Yellow);
	LCD_DrawLine(x+3, y+1, x+8, y+1, Yellow);
	LCD_DrawLine(x+2, y+2, x+9, y+2, Yellow);
	LCD_DrawLine(x+1, y+3, x+8, y+3, Yellow);
	LCD_DrawLine(x+1, y+4, x+6, y+4, Yellow);
	LCD_DrawLine(x+1, y+5, x+4, y+5, Yellow);
	LCD_DrawLine(x+1, y+6, x+6, y+6, Yellow);
	LCD_DrawLine(x+1, y+7, x+8, y+7, Yellow);
	LCD_DrawLine(x+2, y+8, x+9, y+8, Yellow);
	LCD_DrawLine(x+3, y+9, x+8, y+9, Yellow);
	return;
}


void disegnaPacmanUp(int i, int j){ // Bocca rivolta verso l'alto
	if(i >= DIM || j >= DIM) return;
	int x = i*10+10, y = j*10+40;
	LCD_DrawLine(x, y+3, x, y+6, Yellow);
	LCD_DrawLine(x+1, y+2, x+1, y+7, Yellow);
	LCD_DrawLine(x+2, y+1, x+2, y+8, Yellow);
	LCD_DrawLine(x+3, y+2, x+3, y+9, Yellow);
	LCD_DrawLine(x+4, y+4, x+4, y+9, Yellow);
	LCD_DrawLine(x+5, y+6, x+5, y+9, Yellow);
	LCD_DrawLine(x+6, y+4, x+6, y+9, Yellow);
	LCD_DrawLine(x+7, y+2, x+7, y+9, Yellow);
	LCD_DrawLine(x+8, y+1, x+8, y+8, Yellow);
	LCD_DrawLine(x+9, y+2, x+9, y+7, Yellow);
	return;
}

void disegnaPacmanDown(int i, int j){ // Bocca rivolta verso il basso
	if(i >= DIM || j >= DIM) return;
	int x = i*10+10, y = j*10+40;
	LCD_DrawLine(x, y+4, x, y+7, Yellow);
	LCD_DrawLine(x+1, y+3, x+1, y+8, Yellow);
	LCD_DrawLine(x+2, y+2, x+2, y+9, Yellow);
	LCD_DrawLine(x+3, y+1, x+3, y+8, Yellow);
	LCD_DrawLine(x+4, y+1, x+4, y+6, Yellow);
	LCD_DrawLine(x+5, y+1, x+5, y+4, Yellow);
	LCD_DrawLine(x+6, y+1, x+6, y+6, Yellow);
	LCD_DrawLine(x+7, y+1, x+7, y+8, Yellow);
	LCD_DrawLine(x+8, y+2, x+8, y+9, Yellow);
	LCD_DrawLine(x+9, y+3, x+9, y+8, Yellow);
	return;
}

void cancellaCella(int i, int j){
	
	int x = i*10+10;
	int y = j*10+40;

	
	LCD_DrawLine(x, y, x+9, y, Black);
	LCD_DrawLine(x, y, x, y+9, Black);
	LCD_DrawLine(x, y+9, x+9, y+9, Black);
	LCD_DrawLine(x+9, y, x+9, y+9, Black);
	
	schermo[i][j] = 0;
	
	return;
}

void disegnaPillarS(int i, int j){
	schermo[i][j] = 10;
	countPillar += 1;
	int x, y;
	x = i*10 + 10;
	y = j*10 + 40;
	
	LCD_DrawLine(x+4, y+3, x+4, y+6, White);
	LCD_DrawLine(x+5, y+3, x+5, y+6, White);
	LCD_DrawLine(x+3, y+4, x+6, y+4, White);
	LCD_DrawLine(x+3, y+5, x+6, y+5, White);

}

void disegnaPillarM(int i, int j){
	schermo[i][j] = 50;
	int x, y;
	x = i*10 + 10;
	y = j*10 + 40;
	LCD_DrawLine(x+2, y+4, x+7, y+4, Orange);
	LCD_DrawLine(x+2, y+5, x+7, y+5, Orange);
	
	LCD_DrawLine(x+4, y+2, x+4, y+7, Orange);	
	LCD_DrawLine(x+5, y+2, x+5, y+7, Orange);
	
	LCD_DrawLine(x+3, y+3, x+6, y+3, Orange);	
	LCD_DrawLine(x+3, y+6, x+6, y+6, Orange);	
}

void inizializzaPillars(){
	int i, j;
	volatile int i_rand = 0, j_rand = 0;
	for(i = 0; i < DIM; i++){
		for(j = 0; j < DIM; j++){
			if(schermo[i][j] == 0 && (i != i_start || j != j_start) && (i != DIM/2 - 1 || j != DIM/2 -1) && (i != DIM/2 - 1 || j != DIM/2) && (i != DIM/2 || j != DIM/2 -1) && (i != DIM/2|| j != DIM/2) && countPillar <= 240){
				disegnaPillarS(i, j);
			}
		}
	}
}

void inizializzazioneSchermo(){
	int i, j;
	LCD_Clear(Black);
	GUI_Text(70, 140, (uint8_t *) "PLAY PAC-MAN", Yellow, Blue);
	
	LCD_Clear(Black);
	
	for(i=0; i<DIM; i++){
		for(j=0; j<DIM; j++){
			schermo[i][j] = 0;
		}
	}
	
	for(i=0; i<DIM; i++){
		if(i == 10 || i == 11){
			i++;
		}
		else{
			displaySquare(0, i);
			displaySquare(DIM-1, i);
		}
	}
	
	for(i=0; i<DIM; i++){
		displaySquare(i, 0);
		displaySquare(i, DIM-1);
	}
	disegnaForma(1, 4, 'a');
    disegnaForma(6, 2, 'a');
    disegnaForma(2, 2, 'b');
    disegnaForma(3, 5, 'c');
    disegnaForma(5, 4, 'd');
    disegnaForma(8, 2, 'e');
    disegnaForma(3, 9, 'f');
    disegnaForma(10, 2, 'g');
    disegnaForma(9, 9, 'h');
	
		for(i=0; i<DIM/2; i++){
			for(j=0; j<DIM/2; j++){
				if(schermo[i][j] == -1){
					displaySquare(i, DIM-1-j);
					displaySquare(DIM-1-i, j);
					displaySquare(DIM-1-i, DIM-1-j);
					
				}
			}
		}
		
		cancellaCella(9, 7);

		GUI_Text(9*10+11, 12*10+32, (uint8_t*) "PAUSE", Yellow, Blue);
		
		GUI_Text(20, 0, (uint8_t *) "COUNTDOWN", White, Black);
		PutChar(49, 20, 6+48, White, Black);
		PutChar(56, 20, 0+48, White, Black);
		PutChar(65, 20, 115, White, Black);
		
		GUI_Text(150, 0, (uint8_t *) "SCORE", White, Black);
		PutChar(152, 20, score%10+48, White, Black);
		PutChar(160, 20, score/10+48, White, Black);
		PutChar(168, 20, score/100+48, White, Black);
		PutChar(176, 20, score/1000+48, White, Black);
		
		disegnaPacmanRight(1, 1);
		inizializzaPillars();
		cancellaCella(10,9);
		cancellaCella(11,9);
		
		LCD_DrawLine(10*10+10,10*10+35,12*10+9,10*10+35,Red);
		disegnaFantasma(i_ghost,j_ghost, Red);
		disegnaPacmanLife(i_life, j_life);
		
		return;
}

int main(void)
{

  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	
	inizializzazioneSchermo();
	inizializzaPillars();
	pause = 1;
	BUTTON_init();

	init_timer(0, 0, 0, 0x3, 0xC8); 						    /* 8us * 25MHz = 200 ~= 0xC8 */
	init_timer(1, 0, 0, 0x3, 0.25*0x1312D0); 
	init_timer(2, 0, 0, 3, 0x1312D0);
	init_timer(2, 0, 1, 3, 0x1312D0);
	
	enable_timer(0);

	init_RIT(0x1312D0);

	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
