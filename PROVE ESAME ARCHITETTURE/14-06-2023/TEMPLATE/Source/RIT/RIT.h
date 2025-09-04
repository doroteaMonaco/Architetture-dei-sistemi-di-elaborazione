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
#define N 4
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
extern int DIFF_MAX_MIN(int buffer[N], unsigned int pos);
extern void svuotaVettore();

extern volatile int count0, count3;
extern int VETT[N];
extern int index;
extern int full;
extern volatile int disable, disableKey1;
extern int diff;
#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
