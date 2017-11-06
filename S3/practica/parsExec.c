#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

int main(int argc, char* argv[]) {
    for (int i = 0; i < 4; ++i) {
        int pid = fork();
        switch (pid) {
            char s[50];
            case 0:
                if (i == 0) execlp("./listaParametros", "a", "b", (char*)0);
                if (i == 1) execlp("./listaParametros", (char*)0);
                if (i == 2) execlp("./listaParametros", "25", "4", (char*)0);
                if (i == 3) execlp("./listaParametros", "1024", "hola", "adios", (char*)0);
                break;
            case -1:
                sprintf(s,"Ha fallado el fork del proceso: %d\n", getpid());
                error_y_exit(s, 1);
                break;
            default:
                break;
        }
    }
    while (wait(NULL) > 0);
}
