
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
	PROCESS* p;
	int	 greatest_ticks = 0;

	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table+NR_TASKS; p++) {
			// if(p->sleep_ticks)
			// {
			// 	p->sleep_ticks--;
			// }
			if(p->active>0){
				if (p->sleep_ticks){
					p->sleep_ticks--;
				}
				else if(p->ticks > greatest_ticks)
				{
					greatest_ticks = p->ticks;
					p_proc_ready = p;
				}
			}
				// if (!p->sleep_ticks){
			// if (!p->sleep_ticks && p->ticks > greatest_ticks)
			// {
			// 	greatest_ticks = p->ticks;
			// 	p_proc_ready = p;
			// }}
		}

		if (!greatest_ticks) {
			for (p = proc_table; p < proc_table+NR_TASKS; p++) {
				p->ticks = p->priority;
			}
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

PUBLIC void sys_prog_sleep(int mill_seconds)
{
	p_proc_ready->sleep_ticks = (mill_seconds*HZ)/1000;
}

PUBLIC void syscall_disp_str(char* str)
{
	disp_str(str);
}

PUBLIC void sys_sem_p(SEMAPHORE* s)
{
	disable_int();
	s->value--;

	if(s->value<0)
	{
		// disp_int(s->value);
			//disp_str("p opt");
		sleep(s->list);
	}
	enable_int();
	milli_delay(NR_SYS_INT_NAP);
	//disp_str("p opt");
}

PUBLIC void sys_sem_v(SEMAPHORE* s)
{
	disable_int();
	s->value++;
	if(s->value<=0)
	{
		wakeup(s->list);

	}
	enable_int();
	// milli_delay(100);
	//disp_str("v opt");
}

PUBLIC void sleep(LIST* list)
{
	
	//disp_str("sleep");
	list->proc[list->p]=p_proc_ready;
	p_proc_ready->active--;
	list->p++;
	// milli_delay(100);
}

PUBLIC void wakeup(LIST* list)
{
	    	
	int i;
	if(!list->p) return;
	list->proc[0]->active++;
	//list->p--;
	//p_proc_ready
	for(i=1;i<=list->p;i++){
		list->proc[i-1]=list->proc[i];
	}
	list->p--;
	// milli_delay(100);
}