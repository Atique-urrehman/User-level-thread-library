#ifndef UTHREAD_H
#define UTHREAD_H

#include <ucontext.h>
#include "tcb.h"
#include "scheduler.h"
#include "uthread_mutex.h"
#include "uthread_cond.h"

#define UTHREAD_STACK_SIZE  64 * 1024

typedef enum { //enum all thread to use..
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_BLOCKED, //block
    THREAD_FINISHED
} uthread_state;

typedef struct {
    int priority;  
} uthread_attr_t;

void uthread_init(int policy);

// create thread
int uthread_create(void (*func)(void *), void *arg, uthread_attr_t *attr);

void uthread_yield();

// exit thread
void uthread_exit();

void uthread_join(int tid);

int uthread_self();

#endif
