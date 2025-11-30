#ifndef UTHREAD_MUTEX_H
#define UTHREAD_MUTEX_H

#include "tcb.h"

// struct for mutex  handling  --mutex
typedef struct uthread_mutex {
    int locked;        
    tcb_t *owner;      
    tcb_t *waitq;      
} uthread_mutex_t;

// init
void uthread_mutex_init(uthread_mutex_t *m);

// lock
void uthread_mutex_lock(uthread_mutex_t *m);

// unlock
void uthread_mutex_unlock(uthread_mutex_t *m);

#endif
