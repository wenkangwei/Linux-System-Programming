#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
typedef void (*fptr)();
typedef struct timeval TimeStruct;

clock_t Then;


void Catcher(int i)
{
    double CPUTime;

    CPUTime = ((double) (clock() - Then)) / CLOCKS_PER_SEC;
    printf("Timer Expired! CPU Time = %f\n", CPUTime);
    Then = clock();
        alarm(1);
}

int main(void)
{
    struct itimerval Timer;

    printf("Clocks per seconds = %d\n\n", CLOCKS_PER_SEC);

    /* Do Catcher when timer expires */
    signal(SIGALRM, (fptr)Catcher);

    /* Set the timer up to expire every 100 ms. */
    Timer.it_interval.tv_sec = 0;
    Timer.it_interval.tv_usec = 1000000;
    Timer.it_value.tv_sec = 0;
    Timer.it_value.tv_usec = 3000000;
    Then = clock(); /* Get Present Clock Ticks */

    setitimer (ITIMER_REAL, &Timer, NULL);
    alarm(1);
    while (1) {
    }
}

