

#include "stm32f4xx.h"

#define COMM_USART						RCC_APB1Periph_USART2
#define COMM_USART_s					USART2
#define COMM_USART_PORT					RCC_AHB1Periph_GPIOA
#define COMM_USART_TX					GPIO_Pin_2
#define COMM_USART_RX					GPIO_Pin_3

#define COMM_RX_BUFF_SIZE				10
#define COMM_CMD_WORD_SIZE				4
#define COMM_EXCUTOR_LIST_SIZE 			20

#define COMM_BOARD_USART				RCC_APB1Periph_USART3
#define COMM_BOARD_USART_s				USART3
#define COMM_BOARD_USART_PORT			RCC_AHB1Periph_GPIOB
#define COMM_BOARD_USART_TX				GPIO_Pin_10
#define COMM_BOARD_USART_RX				GPIO_Pin_11

#define COMM_BOARD_RX_BUFF_SIZE			8
#define COMM_BOARD_CMD_WORD_SIZE		4
#define COMM_BOARD_EXCUTOR_LIST_SIZE 	20

void comm_init();



void comm_IC_send(unsigned char data);
void comm_IC_array_send(unsigned char* data, int len);
void comm_board_IC_send(unsigned char data);
void comm_board_IC_array_send(unsigned char*data, int len);

void comm_IC_init();

void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
