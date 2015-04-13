

#include "stm32f4xx.h"

#ifndef PID
#define PID

#define PID_OUTPUT_PORT				RCC_AHB1Periph_GPIOA
#define PID_OUTPUT_PORT_s			GPIOA
#define PID_OUTPUT_PIN				GPIO_Pin_4
#define PID_OUTPUT_PORT_CHANNEL		DAC_Channel_1
#define PID_OUTPUT_DAC				RCC_APB1Periph_DAC
#define PID_OUTPUT_DAC_s			DAC

#define PID_INPUT_PORT				RCC_AHB1Periph_GPIOC
#define PID_INPUT_PORT_s			GPIOC
#define PID_INPUT_PIN				GPIO_Pin_0
#define PID_INPUT_PORT_CHANNEL		ADC_Channel_10
#define PID_INPUT_ADC				RCC_APB2Periph_ADC1
#define PID_INPUT_ADC_s				ADC1

#define PID_PARA_p					0.3
#define PID_PARA_i					0.5
#define PID_PARA_d					0
#define PID_PARA_setpoint			2000
#define PID_PARA_sum				0
#define PID_PARA_derr				0
#define PID_PARA_delay				10
#define PID_INT_LIMIT				4000

extern double pid_setpoint, pid_z;

void pid_init();
void pid_handler(unsigned short signal);
void pid_setp(double p);
void pid_seti(double i);
void pid_setd(double d);
void pid_setsetpoint(double setpoint);
void pid_setdelay(int delay);
void pid_report_z(unsigned short *result);
void pid_report_err(unsigned short *result);

void pid_auto_report_enable();
void pid_auto_report_disable();

void pid_IC_init();
void pid_IC_reportor();
void pid_IC_outputz(unsigned char channel, int value);
void pid_dac_config();
void pid_adc_config();
void pid_value_signal(unsigned short *signal);

#endif
