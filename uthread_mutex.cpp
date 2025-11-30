#include "uthread_mutex.h"
#include "scheduler.h"
#include "context.h"

//using uthread mutex for control on lock
void uthread_mutex_init(uthread_mutex_t *m) {
    m->locked = 0;
    m->owner = nullptr;
    m->waitq = nullptr;
}

//mutex only one user/process attime
void uthread_mutex_lock(uthread_mutex_t *m) {
    tcb_t *cur = scheduler_current();
    if (!m->locked) { //if lock already means mutex
        m->locked = 1;
        m->owner = cur;
        return;
    }

    cur->state = THREAD_BLOCKED;
    cur->next = m->waitq;
    m->waitq = cur;

    scheduler_tick();
}

void uthread_mutex_unlock(uthread_mutex_t *m) { // mutex
    if (m->owner != scheduler_current()) return;

    if (!m->waitq) {
        m->locked = 0;
        m->owner = nullptr;
        return;
    }
    //go to tcb
    tcb_t *t = m->waitq;
    m->waitq = t->next;

    m->owner = t;
    t->state = THREAD_READY;

    scheduler_add(t);
}
