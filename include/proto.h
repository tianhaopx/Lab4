
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            proto.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

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
/* xiaoge
void TestA();
void TestB();
void TestC(); */
void TaskSystem();
void TaskProducer();
void TaskConsumerA();
void TaskConsumerB();

/* i8259.c */
PUBLIC void put_irq_handler(int irq, irq_handler handler);
PUBLIC void spurious_irq(int irq);

/* clock.c */
PUBLIC void clock_handler(int irq);


/* 以下是系统调用相关 */

PUBLIC  int     sys_get_ticks();        /* sys_call */
PUBLIC  int     sys_disp_str(char* str);
PUBLIC 	 int     sys_sleep(int milli_sec);
PUBLIC  int     sys_sem_p(int m);
PUBLIC  int     sys_sem_v(int m);

/* syscall.asm */
PUBLIC  void    sys_call();             /* int_handler */
PUBLIC  int       get_ticks();
PUBLIC  void    u_disp_str(char* str);
PUBLIC  void    sleep(int milli_sec);
PUBLIC  void    sem_p(int m);
PUBLIC  void    sem_v(int m);


