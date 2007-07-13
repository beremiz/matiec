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

#define print_BOOL(name) printf("  %s = (BOOL) %s\n",#name, name?"TRUE":"FALSE");
#define print_SINT(name) printf("  %s = (SINT) %d\n",#name, name);
#define print_INT(name) printf("  %s = (INT) %d\n",#name, name);
#define print_DINT(name) printf("  %s = (DINT) %d\n",#name, name);
#define print_LINT(name) printf("  %s = (LINT) %d\n",#name, name);
#define print_USINT(name) printf("  %s = (USINT) %u\n",#name, name);
#define print_UINT(name) printf("  %s = (UINT) %u\n",#name, name);
#define print_UDINT(name) printf("  %s = (UDINT) %u\n",#name, name);
#define print_ULINT(name) printf("  %s = (ULINT) %lu\n",#name, name);
#define print_REAL(name) printf("  %s = (REAL) %f\n",#name, (double)name);
#define print_LREAL(name) printf("  %s = (LREAL) %f\n",#name, (double)name);
#define print_TIME(name) {tmp STRING = __time_to_string(name);tmp.body[tmp.len] = 0; printf("  %s = (TIME) %s*s\n",#name, tmp.len, &tmp.body);}
#define print_DATE(name) {tmp STRING = __date_to_string(name);tmp.body[tmp.len] = 0; printf("  %s = (TIME) %*s\n",#name, tmp.len, &tmp.body);}
#define print_TOD(name) {tmp STRING = __tod_to_string(name);tmp.body[tmp.len] = 0; printf("  %s = (TIME) %*s\n",#name, tmp.len, &tmp.body);}
#define print_DT(name) {tmp STRING = __dt_to_string(name);tmp.body[tmp.len] = 0; printf("  %s = (TIME) %*s\n",#name, tmp.len, &tmp.body);}
#define print_STRING(name) printf("  %s = (STRING) {%d, \"%*s\"}\n",#name, name.len, name.len, &name.body);
#define print_BYTE(name) printf("  %s = (BYTE) 0x%2.2x\n",#name, name);
#define print_WORD(name) printf("  %s = (WORD) 0x%d4.4\n",#name, name);
#define print_DWORD(name) printf("  %s = (DWORD) 0x%d8.8\n",#name, name);
#define print_LWORD(name) printf("  %s = (LWORD) 0x%d16.16\n",#name, name);

static int tick = 0;
void timer_notify(sigval_t val)
{
    clock_gettime(CLOCK_REALTIME, &__CURRENT_TIME);
    printf("Tick %d\n",tick);
    config_run__(tick++);
    printf("  Located variables : \n");
#define __LOCATED_VAR(type, name) print_##type(name);
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
