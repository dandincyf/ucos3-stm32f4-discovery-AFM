#include "comm.h"
#include "comm_module.h"

unsigned char rxbuff[COMM_RX_BUFF_SIZE];
unsigned char rxbuff_count;

unsigned char rxbuff_board[COMM_BOARD_RX_BUFF_SIZE+2];
unsigned char rxbuff_count_board;

void comm_IC_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB1PeriphClockCmd(COMM_USART, ENABLE);
	RCC_AHB1PeriphClockCmd(COMM_USART_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = COMM_USART_TX;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	GPIO_InitStructure.GPIO_Pin = COMM_USART_RX;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);

    USART_ITConfig(COMM_USART_s, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART2_IRQn);



	RCC_APB1PeriphClockCmd(COMM_BOARD_USART, ENABLE);
	RCC_AHB1PeriphClockCmd(COMM_BOARD_USART_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = COMM_BOARD_USART_TX;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);

	GPIO_InitStructure.GPIO_Pin = COMM_BOARD_USART_RX;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(COMM_BOARD_USART_s, &USART_InitStructure);
    USART_Cmd(COMM_BOARD_USART_s, ENABLE);

    USART_ITConfig(COMM_BOARD_USART_s, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART3_IRQn);

    for (int i =0;i<COMM_RX_BUFF_SIZE;i++)
    	rxbuff[i] = 0;

}

void comm_IC_send(unsigned char data)
{
	while(USART_GetFlagStatus(COMM_USART_s, USART_FLAG_TXE)==RESET);
	USART_SendData(COMM_USART_s, data);
}

void comm_IC_array_send(unsigned char* data, int len)
{
	int i=0;
	while (i<len)
	{
		comm_IC_send(*(data+i));
		i++;
	}
}

void
USART2_IRQHandler(void)
{
	if (USART_GetITStatus(COMM_USART_s, USART_IT_RXNE) != RESET)
	{
		unsigned char c = USART_ReceiveData(COMM_USART_s);
		rxbuff[rxbuff_count]=c;
		rxbuff_count++;
		if ((rxbuff_count%2)==0)
		{
			unsigned char temp;
			temp = rxbuff[rxbuff_count-1];
			rxbuff[rxbuff_count-1]=rxbuff[rxbuff_count-2];
			rxbuff[rxbuff_count-2]=temp;
		}
		if (rxbuff_count == COMM_RX_BUFF_SIZE)
		{
			USART_ITConfig(COMM_USART_s, USART_IT_RXNE, DISABLE);
			module_msg_dispatch((CMD_STRU*)rxbuff);
			rxbuff_count = 0;
			USART_ITConfig(COMM_USART_s, USART_IT_RXNE, ENABLE);
		}
	}
}



