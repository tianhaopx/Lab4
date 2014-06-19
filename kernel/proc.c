
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "global.h"
#include "proto.h"




/*======================================================================*
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	PROCESS* p;
	int	 greatest_ticks = 0;

	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table+NR_TASKS; p++) {
			//get the greatest ticks
			
			if (p->ready&&(!p->sleep_ticks)&&(p->ticks > greatest_ticks) ){
				
				greatest_ticks = p->ticks;
				p_proc_ready = p;
			}
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

/*======================================================================*
                           sys_process_sleep
 *======================================================================*/
PUBLIC void sys_process_sleep(int mill_seconds,PROCESS * p_proc){
	// disp_str("sleep");
	// disp_int(mill_seconds);
	p_proc->sleep_ticks=mill_seconds;


}

/*======================================================================*
                           sys_disp_str
 *======================================================================*/
PUBLIC void sys_disp_str(char *str,PROCESS * p_proc){
	// printf("%s\n",str);
	disp_str(str);
}

/*======================================================================*
                           sys_sem_p
 *======================================================================*/
PUBLIC void sys_sem_p(SEMAPHORE s,PROCESS *p_proc){
	pv=1;
	s.value--;
	if(s.value<0){
		p_proc->ready=0;
		enQueue(s.p_que,p_proc);
	}
	pv =0;

}

/*======================================================================*
                           sys_sem_v
 *======================================================================*/
PUBLIC void sys_sem_v(SEMAPHORE s,PROCESS *p_proc){
	pv=1;
	s.value++;
	if(s.value<=0){
		if(s.p_que->size){
			PROCESS* ready_pro=deQueue(s.p_que);
			ready_pro->ready=1;
		}
		
	}
	pv =0;
}

/*======================================================================*
                           enQueue
 *======================================================================*/
PUBLIC void enQueue(QUEUE * p_que,PROCESS *p_proc){
	disp_str("enQueue");
	NODE* pnode;
	pnode->p_proc=p_proc;
	if(p_que->size){
		NODE* rearNode=p_que->rear;
		rearNode->next=pnode;
		p_que->rear=pnode;
	}else{
		p_que->front=pnode;
		p_que->rear=pnode;
	}
	p_que->size++;
	

}

/*======================================================================*
                           deQueue
 *======================================================================*/
PROCESS* deQueue(QUEUE* p_que){
	disp_str("deQueue");
	if(p_que->size){
		NODE* pnode=p_que->front;
		PROCESS* p_proc=pnode->p_proc;
		p_que->size--;
		if(p_que->size){
			p_que->front=pnode->next;
		}
		return p_proc;
	}
	return ;
	
}