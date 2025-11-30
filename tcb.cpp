#include <cstdlib>
#include <cstring>
#include <ucontext.h>
#include "tcb.h"
#include "uthread.h"
#include "scheduler.h"

extern int next_tid;

//getting control o thread
static void thread_stub(void (*func)(void *), void *arg) {
    func(arg);
    uthread_exit();
}

//creat new tcb
tcb_t *tcb_create(void (*func)(void *), void *arg, int priority) {
    tcb_t *t = (tcb_t *)malloc(sizeof(tcb_t));
    if (!t) return nullptr;

    t->tid = next_tid++;
    t->priority = priority;
    t->state = THREAD_READY;
    t->next = nullptr;

    getcontext(&t->ctx);

    t->stack = malloc(UTHREAD_STACK_SIZE);
    if (!t->stack) return nullptr;

    //mutex
    t->ctx.uc_stack.ss_sp = t->stack;
    t->ctx.uc_stack.ss_size = UTHREAD_STACK_SIZE; /
    t->ctx.uc_link = nullptr;
    //no 
    makecontext(&t->ctx, (void(*)())thread_stub, 2, func, arg);

    return t;
}

//destroy/end after using tcb
void tcb_destroy(tcb_t *t) {
    if (!t) return;
    free(t->stack);
    free(t);
}
