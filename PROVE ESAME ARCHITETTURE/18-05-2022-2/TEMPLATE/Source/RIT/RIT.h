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
extern int totale_pressioni_con_filtro(unsigned char VETT[], unsigned int n, unsigned char max, unsigned char min);

extern volatile int disable;
extern unsigned char VETT[N];
extern int index;
extern char VAR;
extern int tot;
extern unsigned char MIN;
extern int bit;
extern unsigned char MAX;
extern int count0, count1;


#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
