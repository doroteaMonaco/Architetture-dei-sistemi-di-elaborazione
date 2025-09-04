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
/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);
extern unsigned int vett[N];
extern unsigned int var;
extern void clearvett();
extern unsigned int var_prec;
extern char flag;
extern unsigned int avg_vett(unsigned int *vett1, unsigned int dim, char *flag);
extern unsigned char LSB_negat;
extern unsigned char extract_LSB(unsigned char val);
extern int lampeggio;







#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
