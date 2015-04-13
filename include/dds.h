

#include "stm32f4xx.h"

#ifndef DDS
#define DDS

#define AD9850_OSC_FREQ		125000000u

#define DDS_RESET_PORT	GPIOA
#define DDS_RESET_PIN	GPIO_Pin_6
#define DDS_RESET_CLK	RCC_AHB1Periph_GPIOA

#define DDS_W_CLK_PORT	GPIOA
#define DDS_W_CLK_PIN	GPIO_Pin_5
#define DDS_W_CLK_CLK	RCC_AHB1Periph_GPIOA

#define DDS_FQ_UD_PORT	GPIOA
#define DDS_FQ_UD_PIN	GPIO_Pin_4
#define DDS_FQ_UD_CLK	RCC_AHB1Periph_GPIOA

#define DDS_D7_PORT	GPIOA
#define DDS_D7_PIN		GPIO_Pin_7
#define DDS_D7_CLK		RCC_AHB1Periph_GPIOA

#define DDS_RESET_1()	GPIO_SetBits(DDS_RESET_PORT,(DDS_RESET_PIN))
#define DDS_RESET_0()	GPIO_ResetBits(DDS_RESET_PORT,(DDS_RESET_PIN))

#define DDS_W_CLK_1()	GPIO_SetBits(DDS_W_CLK_PORT,(DDS_W_CLK_PIN))
#define DDS_W_CLK_0()	GPIO_ResetBits(DDS_W_CLK_PORT,(DDS_W_CLK_PIN))

#define DDS_FQ_UD_1()	GPIO_SetBits(DDS_FQ_UD_PORT,(DDS_FQ_UD_PIN))
#define DDS_FQ_UD_0()	GPIO_ResetBits(DDS_FQ_UD_PORT,(DDS_FQ_UD_PIN))

#define DDS_D7_1()		GPIO_SetBits(DDS_D7_PORT,(DDS_D7_PIN))
#define DDS_D7_0()		GPIO_ResetBits(DDS_D7_PORT,(DDS_D7_PIN))

void AD9850_WriteCmd(uint8_t _ucPhase, double _dOutFreq);
void AD9850_InitHard(void);
void AD9850_ResetToSerial(void);

#endif
