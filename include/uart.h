#ifndef UART_H
#define UART_H


#include <stdio.h>


/* prototypes */
void uart_init(void);

int uart_putc(char c, FILE *stream);
char uart_getc(void);


#endif // UART_H
