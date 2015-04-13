

#include "includes.h"
#include "stm32f4xx.h"

#ifndef MODULE
#define MODULE

#include "test_module.h"
#include "comm_module.h"
#include "motor_module.h"
#include "pid_closeloop_modul.h"
#include "dds_module.h"

#define MODULE_MAX_INTERFACES					20
#define MODULE_MAX_MODULES						0xFF
#define MODULE_MAX_TASKS						1
#define MODULE_MSG_LEN							6


struct module_stru
{
	unsigned short module_head;
	void (*dispatch)(void *msg);
	void (*taks_init[MODULE_MAX_TASKS])();
	int  count_tasks;
	unsigned char priors[MODULE_MAX_TASKS];
};



typedef struct msg_stru
{
	unsigned short para1;
	unsigned short para2;
	unsigned short para3;
	unsigned short para4;
	unsigned short para5;
} MSG_STRU;

typedef struct cmd_stru
{
	unsigned short cmd_head;
	unsigned short cmd_word;
	unsigned short para1;
	unsigned short para2;
	unsigned short para3;
} CMD_STRU;

typedef struct data_stru
{
	unsigned short data_head;
	unsigned short data1;
	unsigned short data2;
	unsigned short data3;
	unsigned short data4;
} DATA_STRU;



struct module_stru modules_list[MODULE_MAX_MODULES];


void module_init();
void module_task_init();

void module_msg_dispatch(CMD_STRU *msg);
void module_addtolist(struct module_stru temp, unsigned short head);
void module_msg_render(MSG_STRU *msg,
		unsigned short para1,
		unsigned short para2,
		unsigned short para3,
		unsigned short para4,
		unsigned short para5);

#endif
