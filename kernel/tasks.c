#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"

void TaskSystem() {
	while(1) {
		u_disp_str("sys.");
		milli_delay(1000);
	}
}

void TaskProducer() {
	while(1) {
		u_disp_str("p");
		milli_delay(1000);
	}
}

void TaskConsumerA() {
	while(1) {
		u_disp_str("ca.");
		sleep(3000);
		u_disp_str("ca2.");
	}
}

void TaskConsumerB() {
	while(1) {
		u_disp_str("cb.");
		milli_delay(1000);
	}
}