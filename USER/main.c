#include <stm32f10x.h>
#include <lcd.h>
#include <stdio.h>
#include <uart.h>
#include <string.h>
#include <tim.h>
#include <key.h>
#include <led.h>
#include <i2c.h>








void Delay_Ms(u32 nTime);
void delay_ms(u32 nTime);
void display(u8 mode,u8 status,u32 second);
void display_second(void);



u32 TimingDelay = 0;
u32 TimingDelay4 = 0;
u8 led_status=0x00;
u8 mode=1;
u8 status=1;
u32 second;
u8 set_status=1;
u16 jiance;


u16 count3;


char dsp_str[20];





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
	pwm_init();
	key_init();
	tim4_init(999,71);
	tim2_init(999,71);
	led_init();
	i2c_init();
	second=u32_read(1);

	while(1)
	{
		display(mode,status,second);
	}
}



void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

void delay_ms(u32 nTime)
{
	TimingDelay4 = nTime;
	jiance++;
	while(TimingDelay4 != 0);	
}


void display(u8 mode,u8 status,u32 second)
{
	 sprintf(dsp_str," No %d",mode);
	 LCD_DisplayStringLine(Line2,(u8 *)dsp_str);
	 switch(status)
	 {
	 	case 1:
			sprintf(dsp_str,"      Standby");
			LCD_DisplayStringLine(Line7,(u8 *)dsp_str);
			memset(dsp_str,0,sizeof(dsp_str));
			break;	
		case 2:
			sprintf(dsp_str,"      Setting");
			LCD_DisplayStringLine(Line7,(u8 *)dsp_str);
			memset(dsp_str,0,sizeof(dsp_str));
			break;
		case 3:
			sprintf(dsp_str,"      Running");
			LCD_DisplayStringLine(Line7,(u8 *)dsp_str);
			memset(dsp_str,0,sizeof(dsp_str));
			break;
		case 4:	
			sprintf(dsp_str,"      Pause");
			LCD_DisplayStringLine(Line7,(u8 *)dsp_str);
			memset(dsp_str,0,sizeof(dsp_str));
			break;
	 }
	 sprintf(dsp_str,"     %02d:%02d:%02d",second/3600,second%3600/60,second%3600%60);
	 LCD_DisplayStringLine(Line5,(u8 *)dsp_str);
	 memset(dsp_str,0,sizeof(dsp_str));
}
void display_second()
{
	sprintf(dsp_str,"     %02d:%02d:%02d",second/3600,second%3600/60,second%3600%60);
	 LCD_DisplayStringLine(Line5,(u8 *)dsp_str);
	 memset(dsp_str,0,sizeof(dsp_str));
}
