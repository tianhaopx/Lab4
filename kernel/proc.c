
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"

/*======================================================================*
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	/*
	 * 首先将所有还在sleep的进程的sleep_ticks减一
	 */
	PROCESS* p = proc_table;
	for(;p<proc_table + NR_TASKS;p++) {
		if(p->sleep_ticks>=0) {
			p->sleep_ticks--;
		}
	}

	while(1) {
		p_proc_ready++;
		if(p_proc_ready >= proc_table + NR_TASKS) {
	    		p_proc_ready = proc_table;
		}
		if(p_proc_ready->sleep_ticks<0) {
			/*
			 * 如果进程没有在睡眠，则跳出循环。
			 * 否则会继续调度，即该进程不会执行
			 */
			break;
		}
	}
	
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

PUBLIC int sys_disp_str(char* str)
{
  	disp_str(str);
    	return 0;
}

PUBLIC int sys_sleep(int mills_sec)
{
	p_proc_ready->sleep_ticks = mills_sec * HZ / 1000;
	schedule();
 	return 0;
}

PUBLIC int sys_sem_p(int m)
{
	/*
	 * 你需要在这里处理代码
	 */
	return 0;
}

PUBLIC int sys_sem_v(int m)
{
	/*
	 * 你需要在这里处理代码
	 */

	return 0;
}
