#include "uthread_cond.h"
#include "scheduler.h"

void uthread_cond_init(uthread_cond_t *c) {
    c->waitq = nullptr;
}

// scheduling technique and wait fo rthread/block etc
void uthread_cond_wait(uthread_cond_t *c, uthread_mutex_t *m) {
    tcb_t *cur = scheduler_current();
    cur->state = THREAD_BLOCKED;//

    cur->next = c->waitq;
    c->waitq = cur;
    //on lock
    uthread_mutex_unlock(m);
    
    scheduler_tick();// which and when scheduling is running
    uthread_mutex_lock(m);
}

//give signal when free or in wait 
void uthread_cond_signal(uthread_cond_t *c) {
    if (!c->waitq) return;
    tcb_t *t = c->waitq;//
    c->waitq = t->next;
    t->state = THREAD_READY;
    scheduler_add(t);
}

//uthread wait untill the other process arrive
void uthread_cond_broadcast(uthread_cond_t *c) {
    while (c->waitq) {
        tcb_t *t = c->waitq;
        c->waitq = t->next;
        t->state = THREAD_READY;
        scheduler_add(t);
    }
}
