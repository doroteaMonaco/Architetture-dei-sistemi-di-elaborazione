/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           RIT.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_RIT, funct_RIT, IRQ_RIT .c files
** Correlated files:    lib_RIT.c, funct_RIT.c, IRQ_RIT.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __RIT_H
#define __RIT_H  
#include <stdint.h>


#define DIM 22
extern int i_start, j_start;
extern int schermo[DIM][DIM];
extern int score;
extern int i_life, j_life;
extern int scorePrecedente;
extern int pause;
extern int i_ghost;
extern int j_ghost;
extern int power;
extern int secondspawn;
extern int secondpower;
extern int count;
extern int current_lives_remaining;
extern int flagm;
extern int dead;
extern int victory;
extern int pillarsRemained;
extern int countPillar;


extern void displaySquare(int i, int j);
extern void disegnaPacmanLeft(int i, int j);
extern void disegnaPacmanRight(int i, int j);
extern void disegnaPacmanUp(int i, int j);
extern void disegnaPacmanDown(int i, int j);
extern void cancellaPacman(int i, int j);
extern void disegnaPacmanLife(int i, int j);
extern void cancellaPacmanLife(int i, int j);
extern void disegnaFantasma(int i, int j, int color);
extern void cancellaFantsma(int i, int j);
extern void startGhost();
extern void moveGhost();

/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);

#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
