#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void Usage() {
	printf("Usage:procesos01 arg1 [arg2..argn]\n");
	printf("Este programa crea tantos procesos como argumentos recibe menos 1 de forma concurrente\n");	
}

void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

int main(int argc, char *argv[])
{
	if (argc >= 2) {
		for (int i = 1; i < argc; ++i) {
			int pid = fork();
			if (pid == 0) {
				printf("El argumento %d es %s\n", i, argv[i]);
				exit(0);
			}
			if (pid < 0) {
				error_y_exit("Error en el fork\n", 1);
			}
		}
		int res;
		while ((res = waitpid(-1, NULL, 0)) > 0)
			printf("El hijo que ha terminado ha sido %d\n", res);
	}
	else {
		Usage();
	}
}