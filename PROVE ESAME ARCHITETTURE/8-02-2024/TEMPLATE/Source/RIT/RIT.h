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
extern void svuotaVettore();
extern unsigned char analisi_accuratezza(unsigned char VETT[], unsigned char VETT2[], unsigned int n, char RES[]);


extern unsigned char VETT[N];  
extern unsigned char VETT2[N];
extern volatile int disable;
extern int index, index1, index2;
extern unsigned char media;
extern int VAR;
extern int stop;
extern int count1, count2;
extern char RES[N];


#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
