#include "apue.h"

static void	sig_usr(int);	/* one handler for both signals */

int
main(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR2");
    if (signal(SIGTERM, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGTERM");
    /* if (signal(SIGKILL, sig_usr) == SIG_ERR) */
    /*     err_sys("can't catch SIGKILL"); */
	for ( ; ; )
		pause();
}

static void
sig_usr(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
    else if (signo == SIGTERM)
        printf("receive SIGTERM\n");
	else
		err_dump("received signal %d\n", signo);
}
