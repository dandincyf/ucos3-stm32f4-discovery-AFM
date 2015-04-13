#ifndef DDS_USART_LIB
#define DDS_USART_LIB

#include "stm32f4xx.h"
#include "includes.h"

#define RX_BUFF_SIZE	8

extern OS_TCB   DDSReciveCmd;
extern OS_Q cmd_q;

void DDS_USART2_configuration(void);


void USART2_puts(CPU_CHAR* s);

#endif
