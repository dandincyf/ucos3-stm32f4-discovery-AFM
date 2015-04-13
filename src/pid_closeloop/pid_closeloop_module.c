#include "pid_closeloop_modul.h"

void
pid_module_init()
{
	pid_init();

	struct module_stru temp;
	temp.module_head = MOD_PID_HEAD;
	temp.count_tasks = 1;
	temp.dispatch = pid_dispatch;
	temp.taks_init[0] = pid_task_init;

	module_addtolist(temp, MOD_PID_HEAD);
}

void
pid_task_init()
{
	OS_ERR err;
	OSQCreate(&SETQ, "setQ", 10, &err);

	OSTaskCreate(
				(OS_TCB	*)&Pid_Run_TCB,
				(CPU_CHAR	*)"pid Run",
				(OS_TASK_PTR)task_pid_run,
				(void	*)0,
				(OS_PRIO	)3,
				(CPU_STK	*)&Pid_Run_Stk[0],
				(CPU_STK_SIZE)Pid_Run_Stk[1024 / 10],
				(CPU_STK_SIZE)1024,
				(OS_MSG_QTY	)0,
				(OS_TICK	)0,
				(void	*)0,
				(OS_OPT)(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),
				(OS_ERR *)&err
				);

	OSTaskCreate(
				(OS_TCB	*)&Pid_Set_TCB,
				(CPU_CHAR	*)"pid set",
				(OS_TASK_PTR)task_pid_set,
				(void	*)0,
				(OS_PRIO	)2,
				(CPU_STK	*)&Pid_Set_Stk[0],
				(CPU_STK_SIZE)Pid_Set_Stk[64 / 10],
				(CPU_STK_SIZE)64,
				(OS_MSG_QTY	)0,
				(OS_TICK	)0,
				(void	*)0,
				(OS_OPT)(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),
				(OS_ERR *)&err
				);

}

void
pid_dispatch(unsigned short *msg)
{
	OS_ERR err;
	unsigned short temp_task = *(msg+1)>>8;
	switch (temp_task)
	{
	case MOD_PID_TASK_SET:
		OSQPost(&SETQ,msg+1, sizeof(unsigned short)*3, OS_OPT_POST_FIFO, &err);
	}
}

void
pid_render(unsigned short *data, unsigned short des_head, unsigned short des_word, unsigned short ori_task_interface, unsigned short *msg)
{
	*msg = des_head;
	*(msg+1) = des_word;
	*(msg+2) = *data;
	*(msg+3) = *(data+1);
	*(msg+4) = MOD_PID_HEAD;
	*(msg+5) = ori_task_interface;
}

void
task_pid_set(void *p_arg)
{
	OS_ERR err;
	OS_MSG_SIZE size;
	CPU_TS ts;
	char dispatch_flag = 0;

	unsigned short *msg, msg_send[6], data[2];
	while (1)
	{
		msg = OSQPend(&SETQ, 0, OS_OPT_PEND_BLOCKING, &size, &ts, &err);
		switch (*msg)
		{
		case MOD_PID_CMD_SETD:
			pid_setd((double)(*(msg+2))+(double)*((msg+1)));
			data[0] = 0x0000;
			data[1] = 0x0001;
			pid_render(data,MOD_COMM_HEAD,(MOD_COMM_TASK_SEND<<8) + MOD_COMM_CMD_SEND_INT,
					   (MOD_PID_TASK_SET <<8) + MOD_PID_CMD_SETD, msg_send);
			dispatch_flag = 1;
			break;
		case MOD_PID_CMD_SETI:
			pid_seti((double)(*(msg+2))+(double)*((msg+1)));
			data[0] = *(msg+1);
			data[1] = *(msg+2);
			pid_render(data,MOD_COMM_HEAD,(MOD_COMM_TASK_SEND<<8) + MOD_COMM_CMD_SEND_INT,
					   (MOD_PID_TASK_SET <<8) + MOD_PID_CMD_SETI, msg_send);
			dispatch_flag = 1;
			break;
		case MOD_PID_CMD_SETP:
			pid_setp((double)(*(msg+2))+(double)*((msg+1)));
			data[0] = *(msg+1);
			data[1] = *(msg+2);
			pid_render(data,MOD_COMM_HEAD,(MOD_COMM_TASK_SEND<<8) + MOD_COMM_CMD_SEND_INT,
					   (MOD_PID_TASK_SET <<8) + MOD_PID_CMD_SETP, msg_send);
			dispatch_flag =1;
			break;
		case MOD_PID_CMD_SETDELAY:
			pid_setdelay(*(msg+1)+*(msg+2));
			data[0] = *(msg+1);
			data[1] = *(msg+2);
			pid_render(data,MOD_COMM_HEAD,(MOD_COMM_TASK_SEND<<8) + MOD_COMM_CMD_SEND_INT,
					   (MOD_PID_TASK_SET <<8) + MOD_PID_CMD_SETDELAY, msg_send);
			dispatch_flag = 1;
			break;
		case MOD_PID_CMD_SETPOINT:
			pid_setsetpoint(*(msg+1)+*(msg+2));
			data[0] = *(msg+1);
			data[1] = *(msg+2);
			pid_render(data,MOD_COMM_HEAD,(MOD_COMM_TASK_SEND<<8) + MOD_COMM_CMD_SEND_INT,
					   (MOD_PID_TASK_SET <<8) + MOD_PID_CMD_SETPOINT, msg_send);
			dispatch_flag = 1;
			break;
		case MOD_PID_CMD_ASK_REPORT_ERR:
			pid_report_err(data);
			data[1]=0;
			pid_render(data,MOD_COMM_HEAD,(MOD_COMM_TASK_SEND<<8) + MOD_COMM_CMD_SEND_INT,
					   (MOD_PID_TASK_SET << 8) + MOD_PID_CMD_ASK_REPORT_ERR, msg_send);
			dispatch_flag = 1;
			break;
		case MOD_PID_CMD_ASK_REPORT_Z:
			pid_report_z(data+1);
			data[0] = 0;
			pid_render(data,MOD_COMM_HEAD,(MOD_COMM_TASK_SEND<<8) + MOD_COMM_CMD_SEND_INT,
					   (MOD_PID_TASK_SET<<8) + MOD_PID_CMD_ASK_REPORT_Z, msg_send);
			dispatch_flag = 1;
			break;
		case MOD_PID_CMD_MOTOR_STOP:

			{

				msg_send[4] = MOD_MOTOR_HEAD;
				dispatch_flag = 1;
			}
		}
		if (dispatch_flag)
		{
			module_msg_dispatch(msg_send);
			dispatch_flag = 0;
		}
	}
}

void
task_pid_run(void *p_arg)
{
	unsigned short signal;
	while (1)
	{
		pid_value_signal(&signal);
		pid_handler(signal);
	}
}
