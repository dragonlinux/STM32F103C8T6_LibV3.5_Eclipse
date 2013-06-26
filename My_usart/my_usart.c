#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "my_usart.h"

#define BUFFERMAX 256
static u8 UsartBuffer[BUFFERMAX]; //定义将要开辟的缓冲区的大小
static u8 BufferWptr = 0; //缓冲区写指针
static u8 BufferRptr = 0; //缓冲区读指针

USART_InitTypeDef USART_InitStructure;

void BufferWrite(void)
{
	if (BufferWptr == (BufferRptr - 1)) //判断缓冲区是否处于“已写满”的状态
	{
		return; //缓冲区已写满，函数返回
		GPIO_SetBits(GPIOC, GPIO_Pin_8 );
	}
	else
	{
		UsartBuffer[BufferWptr] = USART_ReceiveData(USART1 );
		BufferWptr++;
		BufferWptr = BufferWptr % BUFFERMAX;
	}

}

u8 BufferRead(u8 * data)
{
	if (BufferRptr == BufferWptr)
	{
		return 0;
	}
	else
	{
		*data = UsartBuffer[BufferRptr];
		BufferRptr++;
		BufferRptr = BufferRptr % BUFFERMAX;
		return 1;
	}

}

void my_Usart_Init()
{

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable USART1 Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/* Enable USART2 Clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/**********************引脚分配*****************************/

	// Initialize USART1_Tx 初始化发送
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Initialize USART1_RX 初始化接收
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	/**********************引脚分配*****************************/
	/**********************引脚分配*****************************/

	// Initialize USART2_Tx 初始化发送
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Initialize USART2_RX 初始化接收
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	/**********************引脚分配*****************************/

	/* USART1 and USART2 configuration ------------------------------------------------------*/
	/* USART1 and USART2 configured as follow:
	 - BaudRate = 9600 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	/* Configure the GPIO ports */

	USART_InitStructure.USART_BaudRate = 57600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART1 */
	USART_Init(USART1, &USART_InitStructure);
	USART_Init(USART2, &USART_InitStructure);

	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);

	/* Configure USART2 */

	/* Enable USART2 Receive and Transmit interrupts */
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	/* Enable the USART2 */
	USART_Cmd(USART2, ENABLE);

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	/* Enable the USART2 Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}

void my_Usart2_init()
{

}
