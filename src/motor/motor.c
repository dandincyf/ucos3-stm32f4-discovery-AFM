#include "motor.h"


short motor_origin_point;
int motor_stop_flag;

void motor_init()
{
	motor_IC_init();
	motor_origin_point = 0;
}

int motor_directions()
{
	if (motor_origin_point>0)
		return(1);
	else
		return(0);
}


void motor_auto_forward()
{
	while (motor_continue_check() == MOTOR_GOON)
	{
		motor_step_forward(MOTOR_SINGLE_STEP);
	}
	
}

void motor_auto_backward()
{
	while (motor_continue_check() == MOTOR_GOON)
	{
		motor_step_backward(MOTOR_SINGLE_STEP);
	}
	
}

void motor_step_forward(int step)
{
	int temp = step;
	motor_IC_wakeup();
	motor_IC_dir(MOTOR_DIR_FORWARD);
	while (temp>0)
	{
		motor_IC_one_step();
		temp--;
	}
	motor_IC_sleep();
	motor_origin_point += step;
}

void motor_step_backward(int step)
{
	int temp = step;
	motor_IC_wakeup();
	motor_IC_dir(MOTOR_DIR_BACKWARD);
	while (temp>0)
	{
		motor_IC_one_step();
		temp--;
	}
	motor_IC_sleep();
	motor_origin_point -=step;
}

void motor_origin_set()
{
	motor_origin_point=0;
	
}


void motor_originate()
{
	if (motor_origin_point>0)
	{
		motor_step_backward(motor_origin_point);
	}
	else if (motor_origin_point<0)
	{
		motor_step_forward(motor_origin_point);
	}
	motor_origin_set();
	
}

void motor_stop()
{
	motor_stop_flag = MOTOR_STOP;
}

void
motor_reset_stop()
{
	motor_stop_flag = MOTOR_GOON;
}

unsigned char
motor_check_stop()
{
	return motor_stop_flag;
}

short motor_continue_check()
{
	if (motor_stop_flag == MOTOR_STOP)
		return MOTOR_STOP;
	return MOTOR_GOON;
}

//short motor_getorigin()
//{
//	return motor_origin_point;
//}
