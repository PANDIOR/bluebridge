#include <stm32f10x.h>
#include <lcd.h>
#include <stdio.h>
#include <uart.h>
#include <stdio.h>




u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

u8 tx_buf[20];






int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	SysTick_Config(SystemCoreClock/1000);

	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	uart_init();

	while(1)
	{
		printf("!!!");
		Delay_Ms(3000); 
	}
}



void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
