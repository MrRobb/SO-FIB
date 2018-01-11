#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void Usage() {
	printf("Usage:procesos10 ejecutable [arg2..argn]\n");
	printf("Este programa crea tantos procesos como argumentos recibe menos 1 que luego mutan al programa especificado\n");	
}

void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

int main(int argc, char *argv[])
{
	if (argc >= 2) {
		char *programa = argv[1];
		argv++;
		for (int i = 1; i < argc; ++i) {
			int pid = fork();
			if (pid == 0) {
				execvp(programa, argv);
				error_y_exit("Error en el execvp\n", 1);
			}
			if (pid < 0) {
				error_y_exit("Error en el fork\n", 1);
			}
		}
		int res;
		while ((res = waitpid(-1, NULL, 0)) > 0)
			printf("PARE: fill %d mort\n", res);
	}
	else {
		Usage();
	}
}