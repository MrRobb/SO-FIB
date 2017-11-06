#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int hijos = 0;
int contador = 0;
int pids[10];


void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}

void trata_alarma(int s) 
{
    
}

void trata_muerte_hijo(int s) {
	if (s == SIGCHLD) {
		int pid,res;
		pid = waitpid(-1, &res, WNOHANG);
    	while (pid > 0){
    		char buff[256];
            if (WIFEXITED(res)) {
                sprintf(buff,"Termina el proceso %d con exitcode %d\n",pid, WEXITSTATUS(res));
                write(1, buff, strlen(buff));
            }
            else {
                if (WTERMSIG(res) == SIGUSR1) {
                    sprintf(buff,"Termina el proceso %d por el signal USR1\n",pid);
                }
                else {
                    sprintf(buff,"Termina el proceso %d por el signal %d\n",pid, WTERMSIG(res));
                }
                write(1, buff, strlen(buff));
            }
	        
	        hijos --;
	        contador++;
	        pid = waitpid(-1, &res, WNOHANG);
    	}
    }
}

int main(int argc,char *argv[])
{
    int pid,res;
    char buff[256];		
    struct sigaction sa;
    sigset_t mask;

    /* Evitamos recibir el SIGALRM fuera del sigsuspend */

    sigemptyset(&mask);
    sigaddset(&mask,SIGALRM);
    sigaddset(&mask,SIGCHLD);
    sigprocmask(SIG_BLOCK,&mask, NULL);

    for (hijos=0;hijos<10;hijos++)
    {
    	sprintf(buff, "Creando el hijo numero %d\n", hijos);
    	write(1, buff, strlen(buff)); 
        
        sa.sa_handler = &trata_muerte_hijo;
        sa.sa_flags = SA_RESTART;
        sigfillset(&sa.sa_mask);
        if (sigaction(SIGCHLD, &sa, NULL) < 0) error_y_exit("sigaction", 1);

    	pid=fork();
    	if (pid==0) /* Esta linea la ejecutan tanto el padre como el hijo */
    	{

        	sa.sa_handler = &trata_alarma;
        	sa.sa_flags = SA_RESTART;
        	sigfillset(&sa.sa_mask);
    	    if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction", 1);

    	    /* Escribe aqui el codigo del proceso hijo */
      	    sprintf(buff,"Hola, soy %d\n",getpid());
    	    write(1, buff, strlen(buff)); 

    	    alarm(1); 
    	    sigfillset(&mask);
            sigdelset(&mask, SIGALRM);
            sigdelset(&mask, SIGUSR1);
            sigdelset(&mask, SIGINT);
            sigsuspend(&mask);

    	    /* Termina su ejecución */
    	    exit(0);
    	} 
    	else if (pid<0) error_y_exit("Error en el fork", 1);
    	else {
            pids[hijos] = pid;
        	sigfillset(&sa.sa_mask);
        	sigdelset(&mask, SIGCHLD);
    	}
    }
    /* Esperamos que acaben los hijos */
    for (int i = 0; i < 10; ++i) {
        kill(pids[i], SIGUSR1);
        ++contador;
    }
    while (hijos > 0) {
        sigsuspend(&mask);
    }
    sprintf(buff,"Valor del contador %d\n", contador);
    write(1, buff, strlen(buff));
    return 0;
}
