

#include "module.h"
#include "scan_control.h"

#ifndef SCAN_MODULE
#define SCAN_MODULE


#define MOD_SCAN_HEAD						0x0010

#define MOD_SCAN_TASK				0x00


OS_Q ScanQ;

static OS_TCB Scan_TCB;
static CPU_STK Scan_Stk[256];


extern void task_scan(void *p_arg);

extern void scan_module_init();
extern void scan_task_init();
extern void scan_dispatch(unsigned short *msg);
extern void scan_render(unsigned short *data, unsigned short des_head, unsigned short des_word, unsigned short ori_task_interface, unsigned short *msg);


#endif 
