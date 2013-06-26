/*
 * GuYuan_Board_YingJiJieSuoQi.c
 *
 *  Created on: 2013-6-25
 *      Author: dragon
 */

#include "stm32f10x.h"
#include "GuYuan_Board_YingJiJieSuoQi.h"
#include "function.h"
#include "My_delay/my_delay.h"

#define Used_Well

#define FUN_UNLOCK   	0x01 //解锁
#define FUN_LOCK   	 	0x02 //闭锁
#define FUN_ID   		0x04 //修改ID
#define FUN_COMFIRM   	0x08 //确认
#define FUN_DENY   		0x09 //否认
#define FUN_ERROR   	0x0A //错误
#define FUN_SCAN     	0x11 //LED确认
#define FUN_LEDCOMFIRM  0x18 //LED确认
#define FUN_BROADCAST   0xFF //广播
unsigned char buffer[128];

extern u8 rcv_buf[256]; //串口中断接收并放入缓冲区
extern u32 rcv_len; //接收到的数据的长度
extern u8 rcv_begin; //
/*******************************************************/

/*******************************************************/
void Rec_USART1(void)
{
	u8 fun;
	if (USART1_Read_frame(buffer))
	{
		fun = *(buffer + 4);
		switch (fun)
		{
			case FUN_UNLOCK: // 开锁
			{
#if  defined Used_Well
				GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction) 1);
#elif defined Company_Use

#endif

				break;
			}
			case FUN_LOCK: // 闭锁
			{
#if  defined Used_Well
				GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction) 0);
#elif defined Company_Use

#endif
				break;
			}
			case FUN_BROADCAST: // 广播
			{
#if  defined Used_Well

#elif defined Company_Use

#endif
				break;
			}
			default:
			{
				break;
			}
		}
	}

}

unsigned char USART1_Read_frame(unsigned char *buffer)
{
	unsigned char len = 0;	   //协议需要

	if (UART_receive_buf(buffer, 1) < 1)
		return 0;

	while (*buffer != 0x68)	   //读针头，直到第一个是0x68才跳出来
	{
		if (UART_receive_buf(buffer, 1) < 1)
			return 0;
	}
	/*******************判断数据是否正确**********************/
	if (UART_receive_buf(buffer + 1, 8) < 8)   //ID 4字节
		return 0;

	if (*(buffer) != *(buffer + 3))   //0x68==0x68
		return 0;

	if (*(buffer + 1) != *(buffer + 2))   //0x35==0x35------>53
		return 0;
	/****************************************************/
	len = *(buffer + 1);

	if (UART_receive_buf(buffer + 9, len - 9) < len - 9)
		return 0;

	if (*(buffer + len - 1) != 0x16)
		return 0;

	if (*(buffer + len - 2) != checkFrame(buffer, len - 2))
		return 0;

	return len;
}

/**
 * @brief  从buf里接收buflen长的数据
 * @param  buf:
 * @param  buflen:
 *
 * @retval s2
 */
s32 UART_receive_buf(u8 *buf, u32 buflen)
{
	s32 iRet = 0;
	u8* p = buf;
	u8 delay = buflen + 5;   //？？？
	while (delay--)
	{
		if (buflen < rcv_len)
			break;
		Delay(1);
	}
	if (buflen > rcv_len)
		return 0;

	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);

	while (buflen)   //从中断写入的rcv_buf里读取buflenge字节的数据到命令判断的buffer里
	{
		*p = rcv_buf[rcv_begin++];
		rcv_buf[rcv_begin - 1] = 0;
		p++;
		rcv_len--;
		iRet++;
		buflen--;

	}
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	return iRet;
}

u8 checkFrame(void *data, u32 datalen)
{
	u8 cksum = 0;
	u8 *p = data;

	while (datalen > 0)
	{
		cksum += *p++;
		datalen--;
	}
	return cksum;
}
