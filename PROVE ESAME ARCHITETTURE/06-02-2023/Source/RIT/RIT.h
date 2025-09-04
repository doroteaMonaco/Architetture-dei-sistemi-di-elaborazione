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

#include "stdint.h"
/* init_RIT.c */
#define N 4

extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
extern void bubbleSort(int arr[], int n);
extern int count0, count1, count2, count3;
extern int index;
extern unsigned int VETT[N];
extern unsigned int VAR1, VAR2;
extern int disable;
extern char alarm;
extern unsigned int somma;


extern unsigned int calcola_somma_prodotto(unsigned int VETT[N], unsigned int n, char *alarm);
extern void svuotaVettore(unsigned int VETT[N], int n);

#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
