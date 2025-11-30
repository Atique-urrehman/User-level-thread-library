#ifndef TCB_H
#define TCB_H

#include <ucontext.h>

// TCB st..
typedef struct tcb {
    int tid;
    int priority;
    int state;         
    ucontext_t ctx;     
    void *stack;        
    struct tcb *next;   
} tcb_t;

//  new TCB
tcb_t *tcb_create(void (*func)(void *), void *arg, int priority);

// free TCB fo other purpose
void tcb_destroy(tcb_t *t);

#endif
