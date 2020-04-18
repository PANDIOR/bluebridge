#include <led.h>










void led_control(u8 led_status)
{
	GPIOD->ODR|=1<<2;
	GPIOC->ODR=(~led_status)<<8;	//因为LED反逻辑，所以先取反再移位
	GPIOD->ODR^=1<<2;
}