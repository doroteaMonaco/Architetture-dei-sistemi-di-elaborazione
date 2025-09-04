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
#define N 50
#include "stdint.h"
/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
extern unsigned char extract2byte(uint32_t val_TC);
extern int val_TC;
extern int buffer[N];
extern unsigned int i;
extern int DIFF_MAX_MIN(int *b, unsigned int c);
extern unsigned char extractbyte(int a);
extern int flag;
extern void clear_buffer();



#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
