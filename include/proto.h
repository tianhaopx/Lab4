
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            proto.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
// #include "proc.h"
/* klib.asm */
PUBLIC void	out_byte(u16 port, u8 value);
PUBLIC u8	in_byte(u16 port);
PUBLIC void	disp_str(char * info);
PUBLIC void	disp_color_str(char * info, int color);

/* protect.c */
PUBLIC void	init_prot();
PUBLIC u32	seg2phys(u16 seg);

/* klib.c */
PUBLIC void	delay(int time);

/* kernel.asm */
void restart();

/* main.c */
void TestA();
void TestB();
void TestC();
void TestD();

/* i8259.c */
PUBLIC void put_irq_handler(int irq, irq_handler handler);
PUBLIC void spurious_irq(int irq);

/* clock.c */
PUBLIC void clock_handler(int irq);


/* 以下是系统调用相关 */
/* proc.c */
PUBLIC  int     sys_get_ticks();        /* sys_call */
PUBLIC  void	sys_process_sleep(int mill_seconds,PROCESS* p_proc);
PUBLIC  void 	sys_disp_str(char* str,PROCESS* p_proc);
PUBLIC	void 	sys_sem_p(SEMAPHORE s,PROCESS* p_proc);
PUBLIC	void	sys_sem_v(SEMAPHORE s,PROCESS* p_proc);

/* syscall.asm */
PUBLIC  void    sys_call();             /* int_handler */
PUBLIC  int     get_ticks();
PUBLIC  void	process_sleep(int mill_seconds);
PUBLIC  void 	my_disp_str(char *str);
PUBLIC	void	sem_p(SEMAPHORE s);
PUBLIC 	void 	sem_v(SEMAPHORE s);

PUBLIC void enQueue(QUEUE * p_que,PROCESS *p_proc);
PUBLIC PROCESS* deQueue(QUEUE* p_que); 
