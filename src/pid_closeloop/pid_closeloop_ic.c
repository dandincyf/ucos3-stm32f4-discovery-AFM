#include "pid_clooseloop.h"

void pid_IC_init()
{
	pid_dac_config();
	pid_adc_config();
}

void pid_dac_config()
{
	DAC_InitTypeDef DAC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(PID_OUTPUT_PORT, ENABLE);
	RCC_APB1PeriphClockCmd(PID_OUTPUT_DAC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = PID_OUTPUT_PIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(PID_OUTPUT_PORT_s, &GPIO_InitStructure);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;

	DAC_Init(PID_OUTPUT_PORT_CHANNEL, &DAC_InitStructure);
	DAC_Cmd(PID_OUTPUT_PORT_CHANNEL, ENABLE);
	DAC_SetChannel1Data(DAC_Align_12b_R,0x000);
	DAC_SoftwareTriggerCmd(PID_OUTPUT_PORT_CHANNEL, ENABLE);
}

void
pid_adc_config()
{
	GPIO_InitTypeDef 		GPIO_InitStructure;
	ADC_InitTypeDef 		ADC_InitStructure;
	ADC_CommonInitTypeDef	ADC_CommonInitStructure;

	RCC_AHB1PeriphClockCmd(PID_INPUT_PORT, ENABLE);
	RCC_APB2PeriphClockCmd(PID_INPUT_ADC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = PID_INPUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(PID_INPUT_PORT_s, &GPIO_InitStructure);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(PID_INPUT_ADC_s, &ADC_InitStructure);
	ADC_RegularChannelConfig(PID_INPUT_ADC_s, PID_INPUT_PORT_CHANNEL, 1, ADC_SampleTime_144Cycles);

	ADC_Cmd(PID_INPUT_ADC_s, ENABLE);
	ADC_SoftwareStartConv(PID_INPUT_ADC_s);
}

void
pid_IC_outputz(unsigned char channel, int value)
{
	if (channel == DAC_Channel_1)
	{
		DAC_SetChannel1Data(DAC_Align_12b_R, value & 0xfff);
		DAC_SoftwareTriggerCmd(PID_OUTPUT_PORT_CHANNEL, ENABLE);
	}
	else
	{
		DAC_SetChannel2Data(DAC_Align_12b_R, value & 0xfff);
	}
}

void
pid_value_signal(unsigned short *signal)
{
	*signal = ADC_GetConversionValue(PID_INPUT_ADC_s);
}
