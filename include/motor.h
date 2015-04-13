
#ifndef MOTOR
#define MOTOR

#include "stm32f4xx.h"
#define MOTOR_PORT		RCC_AHB1Periph_GPIOE
#define MOTOR_PORT_s	GPIOE
#define MOTOR_DIR		GPIO_Pin_11
#define MOTOR_WAKEUP	GPIO_Pin_13
#define MOTOR_SQUARE	GPIO_Pin_15

void motor_init();

#define MOTOR_DIR_FORWARD		1
#define MOTOR_DIR_BACKWARD		2
#define MOTOR_STEP_DELAY		20000

void motor_IC_one_step();
void motor_IC_dir(int dir);
void motor_IC_sleep();
void motor_IC_wakeup();
void motor_IC_init();


void motor_init();
void motor_auto_forward();
void motor_auto_backward();
void motor_stop();
void motor_reset_stop();
unsigned char motor_check_stop();
void motor_step_forward(int step);
void motor_step_backward(int step);

void motor_originate();
void motor_origin_set();

int motor_getorigin();
int motor_directions();



#define MOTOR_SINGLE_STEP		2

short motor_continue_check();
#define MOTOR_STOP 1
#define MOTOR_GOON 0

#endif
