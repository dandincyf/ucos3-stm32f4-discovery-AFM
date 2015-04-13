

#include "module.h"
#include "dds.h"

#ifndef MODULE_DDS
#define MODULE_DDS

#define MOD_DDS_HEAD						0x0004

#define MOD_DDS_TASK_FREQUENCE				0x00

#define MOD_DDS_CMD_ENABLE					0x00
#define MOD_DDS_CMD_SET_FREQUENCY			0x01

OS_Q FREQ;

static OS_TCB DDS_Frequency_TCB;
static CPU_STK DDS_Frequency_STK[128];

void task_dds_frequency(void *p_arg);

void dds_module_init();
void dds_task_init();
void dds_dispatch(unsigned short *msg);
void dds_render(unsigned short *data, unsigned short des_head, unsigned short des_word, unsigned short ori_task_interface, unsigned short *msg);

#endif
