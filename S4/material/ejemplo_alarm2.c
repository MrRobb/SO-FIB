#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}

/* ESTA VARIABLE SE ACCEDE DESDE LA FUNCION DE ATENCION AL SIGNAL Y DESDE EL MAIN */
int segundos=0;
/* FUNCION DE ATENCION AL SIGNAL SIGALRM */
void funcion_alarma(int s)
{
    char buff[256];
    segundos=segundos+10;
    sprintf(buff, "ALARMA pid=%d: %d segundos\n",getpid(),segundos);
    write(1, buff, strlen(buff)); 
}
int main (int argc,char * argv[])
{
    struct sigaction sa;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_BLOCK,&mask, NULL);

    /* REPROGRAMAMOS EL SIGNAL SIGALRM */
    sa.sa_handler = &funcion_alarma;
    sa.sa_flags = SA_RESTART; 
    sigfillset(&sa.sa_mask); 

    if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction", 1);

    while (segundos<100)
    {
	alarm(10); 	/* Programamos la alarma para dentro de 10 segundos */
		  	/* Nos bloqueamos a esperar que nos llegue un evento */
	sigfillset(&mask);
        sigdelset(&mask, SIGALRM);
	sigdelset(&mask, SIGINT);
        sigsuspend(&mask);
    }
    exit(1);
}
