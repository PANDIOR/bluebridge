#ifndef __led_h_
#define __led_h_
#include <stm32f10x.h>





extern u8 led_status;



void led_init(void);
void led_control(u8 led_status);





#endif
