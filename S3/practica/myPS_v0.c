#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

/* Ejecuta el comando ps –u username mediante la llamada al sistema execlp */
/* Devuelve: el código de error en el caso de que no se haya podido mutar */
void muta_a_PS(char *username) {
	execlp("ps", "ps", "-u", username, (char*)NULL);
	error_y_exit("Ha fallado la mutación al ps", 1);
}

int main(int argc, char* argv[]) {
	if (argc == 2) {
		int ret = fork();
		char s[50];
		switch (ret) {
			case 0:
				sprintf(s, "Soy el proceso HIJO: %d de %s\n", getpid(), argv[1]);
				write(1, s, strlen(s));
				muta_a_PS(argv[1]);
				while(1);
				break;
			case -1:
				sprintf(s,"Ha fallado el fork del proceso: %d\n", getpid());
				error_y_exit(s, 1);
				break;
			default:
				sprintf(s, "Soy el proceso PADRE: %d\n", getpid());
				write(1, s, strlen(s));
				while(1);
				break;
		}
	}
}
