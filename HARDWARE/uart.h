#ifndef __uart_h_
#define __uart_h_
#include <stm32f10x.h>
#include <stdio.h>
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
void uart_init(void);


#endif
