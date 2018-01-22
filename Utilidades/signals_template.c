#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int c = 0;

void ras(int s)
{
	write(1, "Signal.\n", 8);
	if (++c == 3)
		exit(0);
	kill(getpid(), SIGUSR1);
}

int main()
{
	sigset_t mask;
	struct sigaction sa;

	// Block signals
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, NULL);

	// Reprogram SIGUSR1
	sa.sa_handler = ras;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);

	// Wait
	sigfillset(&mask);
	sigdelset(&mask, SIGUSR1);
	sigdelset(&mask, SIGINT);
	printf("Kill me: %d\n", getpid());
	while(1) sigsuspend(&mask);
}