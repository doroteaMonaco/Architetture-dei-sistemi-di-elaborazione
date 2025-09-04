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
extern int VETT[N];
extern volatile int disable;
extern int index;
extern int diff;
extern char over;
extern int count1, count2;
extern int countBuffer;

extern void RIT_IRQHandler (void);
extern void bubbleSortAscending(int arr[], int n);
extern void bubbleSortDescending(int arr[], int n);
extern void clearVett();
extern int differenza_media_positivi_negativi(int VETT[N], unsigned int num, char *over);


#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
