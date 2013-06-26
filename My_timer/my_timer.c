#include "stm32f10x.h"

/**
 * @brief  TIM2初始化
 * @param  None
 * @retval None
 */
void my_Timer2_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable TIM2 Clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_DeInit(TIM2 );
	TIM_TimeBaseStructure.TIM_Period = SystemCoreClock / 10000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM_ClearFlag(TIM2, TIM_FLAG_Update );
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the TIM2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void my_Timer3_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable TIM2 Clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_DeInit(TIM3 );
	TIM_TimeBaseStructure.TIM_Period = 24000000 / 1000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//TIM_ClearFlag(TIM2, TIM_FLAG_Update );
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the TIM2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void SysTick_Configuration(void)
{
	/* Select AHB clock(HCLK) as SysTick clock source 设置AHB时钟为SysTick时钟*/
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK );

	/* Set SysTick Priority to 3 设置SysTicks中断抢占优先级 3， 从优先级0*/
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//NVIC_SystemHandlerPriorityConfig(SysTick_IRQn, 3, 0);
	//有问题：
	/* SysTick interrupt each 1ms with HCLK equal to 32MHz 每1ms发生一次SysTick中断*/
	//SysTick_SetReload(36000);
	/* Enable the SysTick Interrupt */
	//SysTick_ITConfig(ENABLE);
//	SysTick_Config(72000000 / 1000);
	//SysTick_CounterCmd(SysTick_Counter_Enable); //启动 SysTick 计数器
	//有问题：
	if (SysTick_Config(SystemCoreClock / 1000))	//其实开启systick只要这一个函数
	{
		/* Capture error */
		while (1)
			;
	}
}
