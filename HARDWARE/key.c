#include <key.h>

void key_init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/* Configure PA.00 pin as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Enable AFIO clock */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* Connect EXTI0 Line to PA.00 pin */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);
	/* Configure EXTI0 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
//	delay_ms(10);
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
		if (mode == 5)
			mode = 1;
		else
			mode++;
	}
}

void EXTI9_5_IRQHandler(void)
{
//	delay_ms(10);
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) != 1)
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		if (status != 2)
		{
			status = 2;
			set_status = 0;
		}
		if (set_status == 3)
			set_status = 1;
		else
			set_status++;
	}
}
void EXTI1_IRQHandler(void)
{

//	delay_ms(10);
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		TIM_Cmd(TIM2, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line1);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			if (count3 > 800)
			{
				if (status == 2)
					switch (set_status)
					{
					case 1:
						if (second / 3600 >= 23)
						{
							second = second % 3600;
						}
						else
						{
							second += 3600;
						}
						break;
					case 2:
						if ((second % 3600) / 60 >= 59)
						{
							second = second - 59 * 60;
						}
						else
						{
							second += 60;
						}
						break;
					case 3:
						if (second % 3600 % 60 >= 59)
						{
							second = second - 59;
						}
						else
						{
							second += 1;
						}
						break;
					default:;
					}
				display_second();
				delay_ms(50);
			}
		}
		TIM_Cmd(TIM2, DISABLE);
		if (count3 > 800)
			count3 = 0;

		else if (status == 2)
			switch (set_status)
			{
			case 1:
				if (second / 3600 >= 23)
				{
					second = second % 3600;
				}
				else
				{
					second += 3600;
				}
				break;
			case 2:
				if ((second % 3600) / 60 >= 59)
				{
					second = second - 59 * 60;
				}
				else
				{
					second += 60;
				}
				break;
			case 3:
				if (second % 3600 % 60 >= 59)
				{
					second = second - 59;
				}
				else
				{
					second += 1;
				}
				break;
			default:;
			}
		display_second();
	}
	
}
void EXTI2_IRQHandler(void)
{
//	delay_ms(10);
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0)
	{
	   EXTI_ClearITPendingBit(EXTI_Line2);
		if (status != 3)
		{
			status = 3;
		}
		else if (status == 3)
		{
			status = 4;
		}
		printf("!!!");
		display_second();
	}
	
}
