
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            proto.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* klib.asm */
#include"proc.h"                                                    
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
void Normal();
void Producer();
void Consumer_1();
void Consumer_2();

/* i8259.c */
PUBLIC void put_irq_handler(int irq, irq_handler handler);
PUBLIC void spurious_irq(int irq);

/* clock.c */
PUBLIC void clock_handler(int irq);

/* 以下是系统调用相关 */

/* proc.c */
PUBLIC  int     sys_get_ticks();        /* sys_call */
PUBLIC	void	sys_prog_sleep(int mill_seconds);
PUBLIC	void 	syscall_disp_str(char* str);
PUBLIC	void	sys_sem_p(SEMAPHORE* s);
PUBLIC	void	sys_sem_v(SEMAPHORE* s);
//PUBLIC void sleep(LIST* list);

/* syscall.asm */
PUBLIC  void    sys_call();             /* int_handler */
PUBLIC  int     get_ticks();
PUBLIC	void	progress_sleep();
PUBLIC	void 	sys_disp_str();
PUBLIC	void	sem_p();
PUBLIC	void	sem_v();
