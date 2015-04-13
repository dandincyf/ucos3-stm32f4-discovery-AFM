#include "module.h"
#include "motor.h"

#ifndef MODULE_MOTOR
#define MODULE_MOTOR

#define MOD_MOTOR_HEAD						0x0002

#define MOD_MOTOR_TASK_MOVE									0x00

#define MOD_MOTOR_CMD_SET_ORIGIN						0x00
#define MOD_MOTOR_CMD_AUTO_FORWARD			0x01
#define MOD_MOTOR_CMD_AUTO_BACKWARD			0x02
#define MOD_MOTOR_CMD_STEP_FORWARD				0x03
#define MOD_MOTOR_CMD_STEP_BACKWARD			0x04
#define MOD_MOTOR_CMD_ORIGINATE						0x05

#define MOD_MOTOR_STATUS_FORWARD					0X01
#define MOD_MOTOR_STATUS_BACKWARD					0X00
#define MOD_MOTOR_STATUS_MOVING						0X01
#define MOD_MOTOR_STATUS_STOPPING					0X00



#define MOD_MOTOR_TASK_STOP									0X01

#define MOD_MOTOR_CMD_STOP									0X00



#define MOD_MOTOR_REPORT_STEPS				0x00
#define MOD_MOTOR_REPORT_STOP				0x01
#define MOD_MOTOR_REPORT_ORIGINATE			0x02
#define MOD_MOTOR_REPORT_MOVEMENT			0x03

OS_Q MoveQ;
OS_Q StopQ;

static OS_TCB Motor_Move_TCB;
static CPU_STK Motor_Move_Stk[256];

static OS_TCB Motor_Stop_TCB;
static CPU_STK Motor_Stop_Stk[64];


void task_motor_move(void *p_arg);
void task_motor_stop(void *p_arg);

void motor_module_init();
void motor_task_init();
void motor_dispatch(void *msg);
void motor_render(unsigned short *data, unsigned short des_head, unsigned short des_word, unsigned short ori_task_interface, unsigned short *msg);
void motor_report(void* msg, unsigned short* data);
#endif



