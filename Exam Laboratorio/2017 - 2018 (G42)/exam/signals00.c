#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int hijos;

void Usage() {
	printf("Usage:signals00 ejecutable [arg2..argn]\n");
	printf("Este programa crea tantos procesos como argumentos recibe menos 1 que luego mutan al programa especificado\n");	
}

void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

void print_child(int pid, int status) {
	if (WIFEXITED(status))
    {
        // Ha terminado por culpa de un exit
        int exitcode = WEXITSTATUS(status);
        printf("El proceso %d termina con exit code %d\n", pid, exitcode);
    }

    else {
        // Ha terminado por un signal
        int signalcode = WTERMSIG(status);
        printf("El proceso %d termina con signal code %d\n", pid,  signalcode);
    }
}

void ras(int s) {
	if (s == SIGCHLD) {
		int res;
		int status;
		while ((res = waitpid(-1, &status, WNOHANG)) > 0) {
			print_child(res, status);
			--hijos;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc >= 2) {
		char *programa = argv[1];
		argv++;
		hijos = argc - 1;

		sigset_t mask;
		struct sigaction sa;

		// Block signals
		sigemptyset(&mask);
		sigaddset(&mask, SIGCHLD);
		sigprocmask(SIG_BLOCK, &mask, NULL);

		// Reprogram SIGCHLD
		sa.sa_handler = ras;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGCHLD, &sa, NULL);

		for (int i = 1; i < argc; ++i) {
			int pid = fork();
			if (pid == 0) {
				// Como el proceso muta, se pierde la reprogramación de los signals
				execvp(programa, argv);
				error_y_exit("Error en el execvp", 1);
			}
			if (pid < 0) {
				error_y_exit("Error en el fork", 1);
			}
		}

		sigprocmask(SIG_UNBLOCK, &mask, NULL);

		while (hijos > 0);
	}
	else {
		Usage();
	}
}