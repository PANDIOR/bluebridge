#ifndef __tim_h_
#define __tim_h_
#include <stm32f10x.h>

extern u32 TimingDelay4;
extern u8 status;
extern u32 second;
extern u16 count3;





void pwm_init(void);
void tim4_init(u16 arr,u16 psc);
void tim2_init(u16 arr,u16 psc);
#endif

