#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}

void trat_sigusr1(int s) {
    char buf[80];

    sprintf(buf, "Hijo: SIGUSR1 recibido \n");
    write(1, buf,strlen(buf));
}

void trat_sigalrm(int s) {
    char buf[80];

    sprintf(buf, "Padre: voy a mandar SIGUSR1 \n");
    write(1, buf,strlen(buf));
}

main(int argc, char *argv[]) {
    int i,pid_h;
    char buf [80];
    int delay;
    struct sigaction sa, sa2;
    sigset_t mask;

    if (argc !=2) {
	sprintf(buf, "Usage: %s delayParent \n delayParent: 0|1\n",argv[0]);
	write(2,buf,strlen(buf));
	exit(1);
    }   

    delay = atoi(argv[1]);
    //signal (SIGUSR1, trat_sigusr1);
    sa.sa_handler = &trat_sigusr1;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) < 0) error_y_exit("sigaction", 1);

    //signal (SIGALRM, trat_sigalrm);
    sa2.sa_handler = &trat_sigalrm;
    sa2.sa_flags = SA_RESTART;
    sigfillset(&sa2.sa_mask);
    if (sigaction(SIGALRM, &sa2, NULL) < 0) error_y_exit("sigaction", 1);

    pid_h = fork ();

    if (pid_h == 0) {
	sprintf(buf, "Hijo entrando al pause\n");
	write(1,buf,strlen(buf));
	//pause();
	sigfillset(&mask);
        sigdelset(&mask, SIGUSR1);
        sigdelset(&mask, SIGINT);
        sigsuspend(&mask);
	sprintf(buf, "Hijo sale del pause\n");
	write(1,buf,strlen(buf));
    } else {
	if (delay) {
		alarm(5);
		//pause();
		sigfillset(&mask);
          	sigdelset(&mask, SIGALRM);
        	sigdelset(&mask, SIGINT);
        	sigsuspend(&mask);
	}
	sprintf(buf, "Padre manda signal SIGUSR1\n");
	write(1,buf,strlen(buf));
	if (kill (pid_h, SIGUSR1) < 0) error_y_exit("kill", 1);
	waitpid(-1, NULL, 0);
	sprintf(buf, "Padre sale del waitpid\n");
	write(1,buf,strlen(buf));
    } 
}

