
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            main.c
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
#define N 10
int buffer[N];

SEMAPHORE sput,sget,s2;
LIST sput_l,sget_l,s2_l;
int put_ptr,get_ptr;

// LIST em_l;
void init_semaphore(SEMAPHORE* sema, LIST* sema_l, int k){
	sema_l->p=0;
	sema->value=k;
	sema->list=sema_l;
}
/*======================================================================*
                            kernel_main
 *======================================================================*/
PUBLIC int kernel_main()
{
	disp_str("-----\"kernel_main\" begins-----\n");

	TASK*		p_task		= task_table;
	PROCESS*	p_proc		= proc_table;
	char*		p_task_stack	= task_stack + STACK_SIZE_TOTAL;
	u16		selector_ldt	= SELECTOR_LDT_FIRST;
	int i;
	for (i = 0; i < NR_TASKS; i++) {
		strcpy(p_proc->p_name, p_task->name);	// name of the process
		p_proc->pid = i;			// pid

		p_proc->ldt_sel = selector_ldt;

		memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3],
		       sizeof(DESCRIPTOR));
		p_proc->ldts[0].attr1 = DA_C | PRIVILEGE_TASK << 5;
		memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3],
		       sizeof(DESCRIPTOR));
		p_proc->ldts[1].attr1 = DA_DRW | PRIVILEGE_TASK << 5;
		p_proc->regs.cs	= ((8 * 0) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.ds	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.es	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.fs	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.ss	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.gs	= (SELECTOR_KERNEL_GS & SA_RPL_MASK)
			| RPL_TASK;

		p_proc->regs.eip = (u32)p_task->initial_eip;
		p_proc->regs.esp = (u32)p_task_stack;
		p_proc->regs.eflags = 0x1202; /* IF=1, IOPL=1 */

		p_task_stack -= p_task->stacksize;
		p_proc++;
		p_task++;
		selector_ldt += 1 << 3;
	}

	proc_table[0].ticks = proc_table[0].priority =	50;
	proc_table[1].ticks = proc_table[1].priority =  80;
	proc_table[2].ticks = proc_table[2].priority =  1;
	proc_table[3].ticks = proc_table[3].priority =  1;
	proc_table[0].sleep_ticks = 0;
	proc_table[1].sleep_ticks = 0;
	proc_table[2].sleep_ticks = 0;
	proc_table[3].sleep_ticks = 0;
	proc_table[0].active = 1;
	proc_table[1].active = 1;
	proc_table[2].active = 1;
	proc_table[3].active = 1;
	init_semaphore(&sput,&sput_l,N);
	init_semaphore(&sget,&sget_l,0);
	init_semaphore(&s2,&s2_l,1);
	put_ptr=0;
	get_ptr=0;
	k_reenter = 0;
	ticks = 0;

	p_proc_ready	= proc_table;

        /* 初始化 8253 PIT */
        out_byte(TIMER_MODE, RATE_GENERATOR);
        out_byte(TIMER0, (u8) (TIMER_FREQ/HZ) );
        out_byte(TIMER0, (u8) ((TIMER_FREQ/HZ) >> 8));

        put_irq_handler(CLOCK_IRQ, clock_handler); /* 设定时钟中断处理程序 */
        enable_irq(CLOCK_IRQ);                     /* 让8259A可以接收时钟中断 */
	disp_pos = 0;
	for (i = 0; i < 80*25; i++) {
		disp_str(" ");
	}
	disp_pos = 0;
	restart();

	while(1){}
}

/*======================================================================*
                     	Normal Progress for Task Invoker
 *======================================================================*/
void Normal()
{
	//int i = 0;
	while (1) {
		//disp_str("Normal.");
		//disp_int(get_ticks());
		//syscall_disp_str("hhahdhahhdahdh");
		//sys_prog_sleep(1);
		// sys_sem_v(&empty);
		syscall_disp_str("A ");
		milli_delay(100);
	}
}

/*======================================================================*
                               Producer Task
 *======================================================================*/
void Producer()
{
	//int i = 0x1000;
	while(1){
		//disp_str("Make ");
		//EMAPHORE s;
		sys_sem_p(&sput);
	//	milli_delay(100);
		//sys_sem_p(&s1);
		syscall_disp_str("produce ");
		buffer[put_ptr]=1;
		if(put_ptr>=N-1){
			// syscall_disp_str("Sleep Producer ");
			sys_prog_sleep(100);
		}
		put_ptr=(put_ptr+1)%N;

		//sys_sem_v(&s1);
		sys_sem_v(&sget);
		//disp_str("B.");
		// milli_delay(100);
	}
}

/*======================================================================*
                               Consumer Task
 *======================================================================*/
void Consumer_1()
{
	// int i = 0x2000;
	while(1){
		int i;
		//p_proc_ready->active=0;
		sys_sem_p(&sget);
    	sys_sem_p(&s2);
    	if(get_ptr>=N-1){
    		// syscall_disp_str("Sleep Consumer ");
			sys_prog_sleep(100);
		}
   		//milli_delay(100);
    	i= buffer[get_ptr];
    	syscall_disp_str("consume1 ");
    	get_ptr=(get_ptr+1)%N;
    	sys_sem_v(&s2);
    	sys_sem_v(&sput);
    	//disp_str("Consume 1 ");
    	// milli_delay(100);
	}
}

/*======================================================================*
                               Consumer Task
 *======================================================================*/
void Consumer_2()
{
	//int i = 0x2000;
	while(1){
		int i;
		sys_sem_p(&sget);
    	sys_sem_p(&s2);
    	if(get_ptr>=N-1){
    		// syscall_disp_str("Sleep Consumer ");
			sys_prog_sleep(100);
		}
	 	//milli_delay(100);
    	i= buffer[get_ptr];
    	syscall_disp_str("consume2 ");
    	get_ptr=(get_ptr+1)%N;
    	sys_sem_v(&s2);
    	sys_sem_v(&sput);
    	// disp_str("Consume 2 ");
    	// milli_delay(100);

	}
}