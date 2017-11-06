#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}

int segundos=0;
void funcion_alarma(int signal)
{
	char buff[256];
	segundos=segundos+10;
	sprintf(buff,"ALARMA pid=%d: %d segundos\n",getpid(),segundos);
	write(1, buff, strlen(buff) );
}

int main (int argc,char * argv[])
{
    struct sigaction sa;
    sigset_t mask;

    /* EVITAMOS QUE NOS LLEGUE EL SIGALRM FUERA DEL SIGSUSPEND */
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_BLOCK,&mask, NULL);

    /* REPROGRAMAMOS EL SIGNAL SIGALRM */
    sa.sa_handler = &funcion_alarma;
    sa.sa_flags = SA_RESTART; 
    sigfillset(&sa.sa_mask); 

    if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction", 1);

    if (fork() < 0) error_y_exit("fork", 1);
    while (segundos<100)
    {
	alarm(10);
	sigfillset(&mask);
        sigdelset(&mask, SIGALRM);
        sigdelset(&mask, SIGINT);
        sigsuspend(&mask);
    }
    exit(1);
}
