

#ifndef SCAN_CONTROL
#define SCAN_CONTROL

#include "stm32f4xx.h"

#define	SCAN_OUTPUT_PORT					GPIOA
#define SCAN_OUTPUT_PORT_RCC			RCC_AHB1Periph_GPIOA
#define	SCAN_OUTPUT_DAC_RCC			RCC_APB1Periph_DAC

#define SCAN_OUTPUT_PIN							GPIO_Pin_4 | GPIO_Pin_5
#define SCAN_OUTPUT_X								DAC_Channel_1
#define SCAN_OUTPUT_Y								DAC_Channel_2

typedef enum
{
	SCAN_X=SCAN_OUTPUT_X,
	SCAN_Y=SCAN_OUTPUT_Y
}SCAN_DIR;

extern void scan_init(void);
extern void scan_ic_output(SCAN_DIR dir,uint16_t value);
extern void inc_x();
extern void inc_y();
extern void set_inc(uint32_t inc_x,uint32_t inc_y);
extern void set_x(uint16_t value);
extern void set_y(uint16_t value);

#endif
