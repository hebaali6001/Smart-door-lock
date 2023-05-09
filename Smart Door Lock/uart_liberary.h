

#ifndef UART_LIBERARY_H
#define	UART_LIBERARY_H
#include "config.h"

void UART_initi(int BR);

void UART_write_ch(char ch);

void UART_write_str(char str[]);

char UART_read_ch(void);

void UART_read_str(char str[]);

void UART_RCIF_INTERRUPT(void);

void UART_TXIF_INTERRUPT(void);

#endif	/* UART_LIBERARY_H */

