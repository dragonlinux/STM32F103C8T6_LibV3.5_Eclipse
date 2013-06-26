/*
 * function.c
 *
 *  Created on: 2013-6-20
 *      Author: dragon
 */

#include "stm32f10x.h"
#include "function.h"
#include "My_delay/my_delay.h"

void ALL_IO_Toggle()
{
#if defined My_STM32F100_Discovery
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 );
	Delay(100);
	GPIO_SetBits(GPIOB, GPIO_Pin_0 );
	Delay(100);

	GPIO_ResetBits(GPIOB, GPIO_Pin_1 );
	Delay(100);
	GPIO_SetBits(GPIOB, GPIO_Pin_1 );
	Delay(100);

	GPIO_ResetBits(GPIOB, GPIO_Pin_2 );
	Delay(100);
	GPIO_SetBits(GPIOB, GPIO_Pin_2 );
	Delay(100);

	GPIO_ResetBits(GPIOC, GPIO_Pin_8 );
	Delay(100);
	GPIO_SetBits(GPIOC, GPIO_Pin_8 );
	Delay(100);

	GPIO_ResetBits(GPIOC, GPIO_Pin_9 );
	Delay(100);
	GPIO_SetBits(GPIOC, GPIO_Pin_9 );
	Delay(100);
#elif defined  My_STM32F103
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 );
	Delay(500);
	GPIO_SetBits(GPIOB, GPIO_Pin_5 );
	Delay(500);

	GPIO_ResetBits(GPIOB, GPIO_Pin_7 );
	Delay(500);
	GPIO_SetBits(GPIOB, GPIO_Pin_7 );
	Delay(500);
#elif defined  My_STM32F103_Other_Board

#endif
}
