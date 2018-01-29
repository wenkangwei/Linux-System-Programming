#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
typedef void (*fptr)();
typedef struct timeval TimeStruct;

struct timeval Time0;

int SubtractTimevals(TimeStruct *result, TimeStruct *x, TimeStruct *y)
{
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait. tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

void Catcher(int i)
{
    struct timeval DiffTime, Time1;

    /* Calculate time interval since last expiration */
    gettimeofday(&Time1, NULL);
    SubtractTimevals(&DiffTime, &Time1, &Time0);
    gettimeofday(&Time0, NULL);
    printf("Timer Expired! Time Difference = %d s, %d us\n", DiffTime.tv_sec, DiffTime.tv_usec);
    alarm(1);
}

int main(void)
{
    struct itimerval Timer;

    /* Do Catcher when timer expires */
    signal(SIGALRM, (fptr)Catcher);

    /* Set the timer up to expire every 100 ms. */
    // Timer.it_interval.tv_sec = 0;
    // Timer.it_interval.tv_usec = 100000;
    // Timer.it_value.tv_sec = 0;
    // Timer.it_value.tv_usec = 100000;
    // setitimer (ITIMER_REAL, &Timer, NULL);
    gettimeofday(&Time0, NULL);
    alarm(1);

    while (1) {
    }
}

