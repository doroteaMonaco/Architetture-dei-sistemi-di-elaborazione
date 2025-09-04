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
#define N 5
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
extern void svuotaVettore();
extern int compute_sum_and_ranges(unsigned short int VETT[], int index, char lowerB, char upperB, int *rc);

extern volatile int disable;
extern unsigned short int VETT[N];
extern int count0, count1, count2, count3;
extern int index;
extern char lowerB, upperB;
extern int rc;
extern int somma;
extern int VAR;


#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
