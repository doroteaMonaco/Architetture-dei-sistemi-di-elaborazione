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
#define N 6
#include "stdio.h"
#include "stdint.h"

/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
extern uint32_t cs;
extern unsigned char extractbyte(uint32_t VAR);
extern unsigned char extractopposite(unsigned char VAR);
extern int lampeggio;
extern unsigned char led07, led07inv;
extern uint32_t value, vett[N];
extern int i;
extern unsigned char contatore_inrange(uint32_t *VETT1, const unsigned int N1);

extern void clear_vett();
extern int flag;
extern int first;







#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
