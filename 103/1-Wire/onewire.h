/*
 * onewire.h
 *
 *  Version 1.0.1
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

// ��� ������ ����������� ����������� ��������� ������� OW_Init
// �� ������� ������������ ����� USART
#include "stm32f10x.h"

// ��������, �� ����� USART ��������� 1-wire
#define OW_USART1
//#define OW_USART2
//#define OW_USART3
//#define OW_USART4


// ���� ����� �������� ���� FreeRTOS, �� �����������������
//#define OW_GIVE_TICK_RTOS

// ������ �������� ������� OW_Send
#define OW_SEND_RESET		1
#define OW_NO_RESET		2

// ������ �������� �������
#define OW_OK			1
#define OW_ERROR		2
#define OW_NO_DEVICE	3

#define OW_NO_READ		0xff

#define OW_READ_SLOT	0xff

unsigned char OW_Init(void);
unsigned char OW_Send(unsigned char sendReset, unsigned char *command, unsigned char cLen, unsigned char *data, unsigned char dLen, unsigned char readStart);

void OW_out_set_as_Power_pin(void);
void OW_out_set_as_TX_pin(void);

#endif /* ONEWIRE_H_ */
