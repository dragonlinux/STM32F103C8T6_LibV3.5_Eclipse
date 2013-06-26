/*
 * my_delay.c
 *
 *  Created on: 2013-6-25
 *      Author: dragon
 */
#include "stm32f10x.h"
#include "my_delay.h"

static __IO uint32_t TimingDelay;

void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;

	while (TimingDelay != 0)
		;
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}
