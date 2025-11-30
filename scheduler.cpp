#include "scheduler.h"
#include "context.h"
#include <cstdlib>

static tcb_t *ready_q = nullptr;
static tcb_t *current = nullptr;
static int sched_policy = SCHED_RR;

//schedular
void scheduler_init(int policy) {
    sched_policy = policy;
}

// add new scedular
void scheduler_add(tcb_t *t) {
    t->next = nullptr;
    if (!ready_q) {
        ready_q = t;
        return;
    }
    tcb_t *p = ready_q;
    while (p->next) p = p->next;
    p->next = t;
}

//pinting... tcb
static tcb_t* rr_pick() {
    if (!ready_q) return nullptr;
    tcb_t *t = ready_q;
    ready_q = ready_q->next;
    t->next = nullptr;
    return t;
}

static tcb_t* prio_pick() {
    if (!ready_q) return nullptr;
    tcb_t *best = ready_q;
    tcb_t *prev = nullptr;

    tcb_t *p = ready_q;
    tcb_t *p_prev = nullptr;
    
    //remain in processing untill the new porcess arrive
    while (p) {
        if (p->priority < best->priority) {
            best = p;
            prev = p_prev;
        }
        p_prev = p;
        p = p->next;
    }
    //using sceduling process
    if (prev) prev->next = best->next;
    else ready_q = best->next;

    best->next = nullptr;
    return best;
}

//using double sceduling, move to next after first process completes.
tcb_t *scheduler_next() {
    if (sched_policy == SCHED_PRIORITY)
        return prio_pick();
    return rr_pick();
}

void scheduler_set_current(tcb_t *t) {
    current = t;
    if (t) t->state = THREAD_RUNNING;
}

//scheduling currently
tcb_t *scheduler_current() {
    return current;
}

void scheduler_tick() {
    tcb_t *old = current;
    //if already thread runnnig in schedule

    if (old && old->state == THREAD_RUNNING) {
        old->state = THREAD_READY;
        scheduler_add(old);
    }

    tcb_t *next = scheduler_next();
    scheduler_set_current(next);

    context_switch(old, next);
}
