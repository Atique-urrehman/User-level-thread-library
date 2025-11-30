#ifndef UTHREAD_COND_H
#define UTHREAD_COND_H

#include "tcb.h"
#include "uthread_mutex.h"

typedef struct uthread_cond {
    tcb_t *waitq;      // wait untill other process exit
} uthread_cond_t;

void uthread_cond_init(uthread_cond_t *c);

// wait 
void uthread_cond_wait(uthread_cond_t *c, uthread_mutex_t *m);

//signal that process busy
void uthread_cond_signal(uthread_cond_t *c);

// broadcast all
void uthread_cond_broadcast(uthread_cond_t *c);

#endif
