#include <time.h>
#include <signal.h>

#include "iec_std_lib.h"

/*
 * Functions and variables provied by generated C softPLC
 **/ 
void config_run__(int tick);
void config_init__(void);
extern int common_ticktime__;

/*
 *  Functions and variables to export to generated C softPLC
 **/
 
TIME __CURRENT_TIME;

#define __LOCATED_VAR(type, name) type name;
#include "LOCATED_VARIABLES.h"
#undef __LOCATED_VAR

static int tick = 0;
void timer_notify(sigval_t val)
{
    clock_gettime(CLOCK_REALTIME, &__CURRENT_TIME);
    printf("Tick %d\n",tick);
    config_run__(tick++);
    printf("  Located variables : \n");
#define __LOCATED_VAR(type, name) __print_##type(name);
#include "LOCATED_VARIABLES.h"
#undef __LOCATED_VAR
}

void catch_signal(int sig)
{
  signal(SIGTERM, catch_signal);
  signal(SIGINT, catch_signal);
  printf("Got Signal %d\n",sig);
}

#define maxval(a,b) ((a>b)?a:b)
int main(int argc,char **argv)
{
    timer_t timer;
    struct sigevent sigev;
    long tv_nsec = 1000000 * (maxval(common_ticktime__,1)%1000);
    time_t tv_sec = common_ticktime__/1000;
    struct itimerspec timerValues;
    
    memset (&sigev, 0, sizeof (struct sigevent));
    memset (&timerValues, 0, sizeof (struct itimerspec));
    sigev.sigev_value.sival_int = 0;
    sigev.sigev_notify = SIGEV_THREAD;
    sigev.sigev_notify_attributes = NULL;
    sigev.sigev_notify_function = timer_notify;
    timerValues.it_value.tv_sec = tv_sec;
    timerValues.it_value.tv_nsec = tv_nsec;
    timerValues.it_interval.tv_sec = tv_sec;
    timerValues.it_interval.tv_nsec = tv_nsec;

    config_init__();

    timer_create (CLOCK_REALTIME, &sigev, &timer);
    timer_settime (timer, 0, &timerValues, NULL);
    
    /* install signal handler for manual break */
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);
    
    pause();
    
    timer_delete (timer);
    
    return 0;
}
