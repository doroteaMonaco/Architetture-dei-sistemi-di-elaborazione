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
#define N 8
#include "stdint.h"
/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
extern int counters;
extern uint32_t VAR1, VAR2, VETT[N];
extern unsigned int calcola_somma_prodotto(unsigned int* v, unsigned int n, char* alarm);
extern int i;
extern int mod;
extern int extractbits(uint32_t* v);
extern int c,co,c3;
extern void clear_vett();

#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
