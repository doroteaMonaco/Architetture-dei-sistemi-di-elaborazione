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
#define N 10
#define M 10
#include "stdint.h"
/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
extern void bubbleSortAscending(int arr[], int n);
extern void bubbleSortDescending(int arr[], int n);
extern char updateRank(char SCORE, char CLASSIFICA[M], char *max_diff, char *PODIO);
extern unsigned short int SEQ[N];
extern int index1;
extern char pos;
extern int fine;
extern int led;
extern int count1, count2;
extern void leggiVettore(unsigned short int SEQ[], int n);
extern char SCORE;
extern volatile int disable;
extern char CLASSIFICA[M];
extern char max_diff;
extern char PODIO;

#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
