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
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
#define N 4
extern unsigned char VETT[N];
extern unsigned char VAL;
extern int index;
extern unsigned char ExtractBits(int value);
extern unsigned char get_and_sort(unsigned char* v, unsigned char va, int n);
extern int indexled;
extern int disable;



#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
