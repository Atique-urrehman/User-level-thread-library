#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <sys/time.h>
#include "uthread.h"
#include "context.h"

static int next_tid = 1;

void uthread_init(int policy) {
    scheduler_init(policy);
    context_setup_timer();
}

//create new thread
int uthread_create(void (*func)(void *), void *arg, uthread_attr_t *attr) {
    int prio = (attr ? attr->priority : 1);
    tcb_t *t = tcb_create(func, arg, prio);
    if (!t)   //return if no new
    return -1; 
    scheduler_add(t);
    return t->tid;
}

//
void uthread_yield() {
    scheduler_tick();
}

//exit from thread
void uthread_exit() {
    tcb_t *cur = scheduler_current();
    cur->state = THREAD_FINISHED;
    scheduler_tick();
}

//join other
void uthread_join(int tid) {
    while (true) {
        tcb_t *cur = scheduler_current();
        //if 
        if (cur->tid == tid && cur->state == THREAD_FINISHED) 
        return;
        uthread_yield();
    }
}

int uthread_self() {
    return scheduler_current()->tid;
}
