#include <led.h>










void led_control(u8 led_status)
{
	GPIOD->ODR|=1<<2;
	GPIOC->ODR=(~led_status)<<8;	//��ΪLED���߼���������ȡ������λ
	GPIOD->ODR^=1<<2;
}