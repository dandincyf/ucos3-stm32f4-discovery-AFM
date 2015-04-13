#include "comm.h"
#include "module.h"

#ifndef MODULE_COMM
#define MODULE_COMM

#define MOD_COMM_HEAD					0x0001

#define MOD_COMM_TASK_SEND				0x00

#define MOD_COMM_CMD_SEND_INT			0x00
#define MOD_COMM_CMD_BOARD_SEND_INT		0x02

#define MOD_COMM_TASK_REPORT			0X01

OS_Q	SendDataQ;

static OS_TCB Comm_Send_TCB;
static CPU_STK Comm_Send_Stk[256];

void task_comm_send(void *p_arg);

void comm_module_init();
void comm_task_init();
void comm_dispatch(void *msg);
void comm_render(unsigned short *data, unsigned short des_head, unsigned short des_word, unsigned short ori_task_interface, unsigned short *msg);
#endif



