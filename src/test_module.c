#include "test_module.h"
#include "stm32f4xx.h"

void task_led_blink(void *p_arg)
{
	unsigned short *cmd;
	OS_MSG_SIZE size;

	CPU_TS ts;

	RCC_AHB1PeriphClockCmd(BLINK_RCC_BIT, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = (1 << BLINK_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(BLINK_PORT, &GPIO_InitStructure);

	unsigned short temp;
	temp=MOD_TEST_CMD_BLINK;

	OS_ERR err;
	MSG_STRU *msg = (MSG_STRU*)malloc(sizeof(MSG_STRU));
	msg->para1 = 1;
	msg->para2 = 1;
	msg->para3 = 1;
	msg->para4 = 1;
	msg->para5 = 1;

	OSQPost(&BlinkQ, &temp, sizeof(unsigned short), OS_OPT_POST_FIFO, &err);

	while (1)
	{
		OS_ERR err;
		cmd = (unsigned short *)OSQPend(&BlinkQ,0,OS_OPT_PEND_BLOCKING,&size,&ts,&err);
		if (*cmd == MOD_TEST_CMD_BLINK)
		{
			GPIO_ResetBits(BLINK_PORT, (1 << BLINK_PIN));
			for (long i=0;i<200000;i++);
			GPIO_SetBits(BLINK_PORT, (1 << BLINK_PIN));
			for (long i=0;i<220000;i++);
			module_msg_render(msg,
						MOD_TEST_HEAD,
						((MOD_TEST_TASK_BLINK<<8) + MOD_TEST_CMD_SET_BLINK),
						0x0000,
						0x0000,
						0x0000);
			module_msg_dispatch((CMD_STRU*)msg);
		}
		else if (*cmd == MOD_TEST_CMD_SET_BLINK)
		{
			module_msg_render(msg,
					MOD_TEST_HEAD,
					((MOD_TEST_TASK_BLINK << 8) + MOD_TEST_CMD_BLINK),
					0x0000,
					0x0000,
					0x0000);
			module_msg_dispatch((CMD_STRU*)msg);
		}
	}
}

void test_module_init()
{
	struct module_stru temp;
	temp.module_head=MOD_TEST_HEAD;
	temp.count_tasks=1;
	temp.dispatch=test_dispatch;
	temp.taks_init[0]=test_task_init;
	module_addtolist(temp, MOD_TEST_HEAD);
}
void test_task_init()
{
	CPU_ERR err;
	OSQCreate(&BlinkQ,"BlinkQ",10,&err);

	OSTaskCreate(
				(OS_TCB	*)&Test_led_blink_TCB,
				(CPU_CHAR	*)"Led Blink",
				(OS_TASK_PTR)task_led_blink,
				(void	*)0,
				(OS_PRIO	)9,
				(CPU_STK	*)&Test_led_blink_STK[0],
				(CPU_STK_SIZE)Test_led_blink_STK[256 / 10],
				(CPU_STK_SIZE)256,
				(OS_MSG_QTY	)0,
				(OS_TICK	)0,
				(void	*)0,
				(OS_OPT)(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),
				(OS_ERR *)&err
				);
}

void test_dispatch(void *msg)
{
	CMD_STRU *temp = msg;
	unsigned short cmd_word = (temp->cmd_word)&0x00FF;

	OS_ERR err;

	switch (temp->cmd_word>>8)
	{
	case MOD_TEST_TASK_BLINK:
	{
		switch ((temp->cmd_word)&0x00FF)
		{
		case MOD_TEST_CMD_BLINK:
			OSQPost(&BlinkQ, &cmd_word, sizeof(unsigned short), OS_OPT_POST_FIFO, &err);
			break;
		case MOD_TEST_CMD_SET_BLINK:
			OSQPost(&BlinkQ, &cmd_word, sizeof(unsigned short), OS_OPT_POST_FIFO, &err);
			break;
		}
		break;
	}
	}
}

