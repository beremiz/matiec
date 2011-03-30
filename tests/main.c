#ifdef __WIN32__
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <windows.h>
#else
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#endif

#include "iec_types.h"

/*
 * Functions and variables provied by generated C softPLC
 **/ 
extern int common_ticktime__;

IEC_BOOL __DEBUG;

/*
 * Functions and variables provied by plc.c
 **/ 
void run(long int tv_sec, long int tv_nsec);

#define maxval(a,b) ((a>b)?a:b)

#ifdef __WIN32__
void timer_notify()
{
   struct _timeb timebuffer;

   _ftime( &timebuffer );
   run(timebuffer.time, timebuffer.millitm * 1000000);
}

int main(int argc,char **argv)
{
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;

    liDueTime.QuadPart = -10000 * maxval(common_ticktime__,1);;

    // Create a waitable timer.
    hTimer = CreateWaitableTimer(NULL, TRUE, "WaitableTimer");
    if (NULL == hTimer)
    {
        printf("CreateWaitableTimer failed (%d)\n", GetLastError());
        return 1;
    }

    config_init__();

    // Set a timer to wait for 10 seconds.
    if (!SetWaitableTimer(hTimer, &liDueTime, common_ticktime__, NULL, NULL, 0))
    {
        printf("SetWaitableTimer failed (%d)\n", GetLastError());
        return 2;
    }

    while(1){
    // Wait for the timer.
        if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)
        {
            printf("WaitForSingleObject failed (%d)\n", GetLastError());
            break;
        }
        timer_notify();
    }
    return 0;
}
#else
void timer_notify(sigval_t val)
{
    struct timespec CURRENT_TIME;
    clock_gettime(CLOCK_REALTIME, &CURRENT_TIME);
    run(CURRENT_TIME.tv_sec, CURRENT_TIME.tv_nsec);
}

void catch_signal(int sig)
{
  signal(SIGTERM, catch_signal);
  signal(SIGINT, catch_signal);
  printf("Got Signal %d\n",sig);
}

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
#endif
