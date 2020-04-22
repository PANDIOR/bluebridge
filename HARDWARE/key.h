#ifndef __key_h_
#define __key_h_
#include <stm32f10x.h>
#include <stdio.h>

extern void delay_ms(u32 nTime);
extern u8 mode;
extern u8 status;
extern u8 set_status;
extern u32 second;
extern u16 count3;




extern void display_second(void);
extern void Delay_Ms(u32 nTime);



void key_init(void);


#endif
