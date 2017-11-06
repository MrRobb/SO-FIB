#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define FIN_BUCLE 50000000ULL

void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}

void hago_algo_util()
{
    unsigned long long  i;

    for (i = 0; i < FIN_BUCLE; i++);
}


void trata_alarma(int s) 
{

}


int main(int argc,char *argv[])
{
    int pid,res;
    char buff[256];		
    int hijos=0;
    struct sigaction sa;
    sigset_t mask;

    for (hijos=0;hijos<10;hijos++)
    {
	sprintf(buff, "Creando el hijo numero %d\n", hijos);
	write(1, buff, strlen(buff)); 
		
	pid=fork();
	if (pid==0) /* Esta linea la ejecutan tanto el padre como el hijo */
	{
	    //signal (SIGALRM, trata_alarma);

            sa.sa_handler = &trata_alarma;
            sa.sa_flags = SA_RESTART;
            sigfillset(&sa.sa_mask);
    	    if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction", 1);

	    /* Escribe aqui el codigo del proceso hijo */
   	    sprintf(buff,"Hola, soy %d\n",getpid());
	    write(1, buff, strlen(buff)); 

	    alarm(1); 
	    //pause();
	    sigfillset(&mask);
            sigdelset(&mask, SIGALRM);
            sigdelset(&mask, SIGINT);
            sigsuspend(&mask);

	    /* Termina su ejecución */
	    exit(0);
	} else if (pid<0)	
	{
	    /* Se ha producido un error */
	    error_y_exit("Error en el fork", 1);
	}
    }

    hago_algo_util();

    /* Esperamos que acaben el resto de  hijos */
    while ((pid=waitpid(-1,&res,0)) > 0) 
    {
	sprintf(buff,"Waitpid bloqueante. Termina %d\n",pid);
	write(1, buff, strlen(buff)); 
    }
    return 0;
}
