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
#define N 10

/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
extern unsigned char ExtractVal(int value);
extern void fill_fibonacci(unsigned char M1);
extern unsigned char check_fibonacci(unsigned char* vett, unsigned char N1, unsigned char M1, unsigned char val, unsigned char BOUNDARY1);
extern unsigned char vett[N];
extern void clean_vett();
extern int discard;




extern int first;




#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
