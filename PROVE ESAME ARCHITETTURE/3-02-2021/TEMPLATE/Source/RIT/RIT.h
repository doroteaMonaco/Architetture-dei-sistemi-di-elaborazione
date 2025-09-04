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
#define N 127

#include "stdint.h"
/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern int monitor;
extern unsigned char valoreIniziale, valoreCorrente;
extern int index;
extern unsigned int tempiVariazioni[N];
extern unsigned int VAL;
extern unsigned char dutyCicle;
extern int count0;

extern unsigned char duty_cycle(unsigned char valore_iniziale, unsigned int tempo_totale,
unsigned int tempi_variazioni[], unsigned char numero_variazioni);

extern void RIT_IRQHandler (void);
extern void bubbleSortAscending(int arr[], int n);
extern void bubbleSortDescending(int arr[], int n);




#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
