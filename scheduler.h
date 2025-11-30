#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "tcb.h"

#define SCHED_RR       1
#define SCHED_PRIORITY 2

//all func of scheduling method --atique
// init 
void scheduler_init(int policy);

// add ready
void scheduler_add(tcb_t *t);

// pick next
tcb_t *scheduler_next();

void scheduler_set_current(tcb_t *t);

// get running
tcb_t *scheduler_current();

void scheduler_tick();

#endif
