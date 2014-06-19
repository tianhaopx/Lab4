
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               clock.c
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
                           clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq)
{
	ticks++;//every second
	p_proc_ready->ticks--;
	PROCESS* p;
	for (p = proc_table; p < proc_table+NR_TASKS; p++) {
			if (p->sleep_ticks>0) {
				p->sleep_ticks--;
			}
		}
	// disp_int(k_reenter);
	if (k_reenter != 0) {
		return;
	}
	//decide which process to run
	if(pv){
		return;
	}

	schedule();
}

/*======================================================================*
                              milli_delay
 *======================================================================*/
PUBLIC void milli_delay(int milli_sec)
{
        int t = get_ticks();

        while(((get_ticks() - t) * 1000 / HZ) < milli_sec) {
        }
}
/*======================================================================*
                              milli_sleep
 *======================================================================*/

// PUBLIC void milli_sleep(int milli_sec){
// 	int t=get_ticks();
// 	while(((get_ticks() - t) * 1000 / HZ) < milli_sec)
// }