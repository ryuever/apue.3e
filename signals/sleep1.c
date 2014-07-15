#include	<signal.h>
#include	<unistd.h>
#include <stdio.h>
#include <sys/times.h>
#include "apue.h"

static long clktck = 0;

static void
sig_alrm(int signo)
{
    int i, j, k;
    
    struct tms tmsstart, tmsend;
    clock_t start, end;

    if (clktck == 0)
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            err_sys("system error");

	/* nothing to do, just return to wake up the pause */
    printf("\nin sig_alrm\n");
    printf("Beginning of for statement in sig_alrm\n");
    if((start = times(&tmsstart)) == -1)
        err_sys("time error");

    for(i=0; i< 300000; i++)
        for(j=0; j<7500; j++)
            k = i * j;
    if((end = times(&tmsend)) == -1)
        err_sys("time error");
    printf("    sys : %7.2f\n",
           (end - start) / (double) clktck);
    printf("Ending of for statement in sig_alrm\n");
}

static void
sig_int(int signo){
    printf("\nin sig_int\n");
}

unsigned int
sleep1(unsigned int seconds)
{
    int  i, j, k;

    struct tms tmsstart, tmsend;
    clock_t start, end;
    
    printf("The beginning of func sleep1\n");
    
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return(seconds);
    if (signal(SIGINT, sig_int) == SIG_ERR)
        return(seconds);
	alarm(seconds);		/* start the timer */

    if((start = times(&tmsstart)) == -1)
        err_sys("time error");
    printf("start time in sleep1 is %lu\n", start);
    
    for(i=0; i< 300000; i++)
        for(j=0; j<7500; j++)
            k = i * j;
    
    if((end = times(&tmsend)) == -1)
        err_sys("time error");

    if (clktck == 0)
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            err_sys("system error");

    printf("\nend time in sleep1 is %lu\n", end);
    
    printf("    sys : %7.2f\n",
           (end - start) / (double) clktck);

    printf("\nbefore func pause\n");
	pause();			/* next caught signal wakes us up */
    printf("after func pause\n");
	return(alarm(0));	/* turn off timer, return unslept time */
}

int main(){
    sleep1(4);
}
