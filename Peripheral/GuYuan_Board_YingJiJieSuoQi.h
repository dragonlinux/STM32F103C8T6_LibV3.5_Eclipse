/*
 * GuYuan_Board_YingJiJieSuoQi.h
 *
 *  Created on: 2013-6-25
 *      Author: dragon
 */

#ifndef GUYUAN_BOARD_YINGJIJIESUOQI_H_
#define GUYUAN_BOARD_YINGJIJIESUOQI_H_





void Rec_USART1(void);
unsigned char USART1_Read_frame(unsigned char *buffer);
s32 UART_receive_buf(u8 *buf, u32 buflen);
u8 checkFrame(void *data, u32 datalen);

#endif /* GUYUAN_BOARD_YINGJIJIESUOQI_H_ */
