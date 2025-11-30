#include <signal.h>
#include <sys/time.h>
#include "context.h"
#include "scheduler.h"


//context swictch for switching the current
void context_switch(tcb_t *old, tcb_t *next) {
    if (!old) { //if old is in use previously
        setcontext(&next->ctx);
        return;
    }
    swapcontext(&old->ctx, &next->ctx);
}

static void timer_handler(int s) {
    scheduler_tick();
}
// timer
void context_setup_timer() {
    struct sigaction sa;
    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGVTALRM, &sa, nullptr);


    struct itimerval timer; //times all
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 5000;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 5000;
    setitimer(ITIMER_VIRTUAL, &timer, nullptr);
}
