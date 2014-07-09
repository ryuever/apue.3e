#include "apue.h"

static void	sig_alrm(int);

int
main(void)
{
	int	n;
    unsigned int alarmRet,alarmRet2;
	char line[MAXLINE];
    
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");

	alarmRet = alarm(10);	
    printf("Testing the time for writing\n");

	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	alarmRet2 = alarm(0);

    printf("The return value of previous alarm is %u\n",alarmRet);
    printf("The return value of previous alarm is %u\n",alarmRet2);
    
	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void
sig_alrm(int signo)
{
	/* nothing to do, just return to interrupt the read */
}
