#include <unistd.h>
#include <stdio.h>
#include <string.h>

char variable_global='A';

void Escribe_variables()
{
char buffer[80];
	sprintf(buffer,"Funcion:La variable_global vale %c y la local %c\n", 
	variable_global,variable_local);
	write(1, buffer, strlen(buffer));
}
int main(int argc,char *argv[])
{
	int pid;
	char buffer[80];
	char variable_local='a';

	sprintf(buffer,"Antes del fork: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));

	pid=fork();
	
	switch (pid){ /* Esta linea la ejecutan tanto el padre como el hijo */
		case 0: /* Escribe aqui el codigo del proceso hijo */
			sprintf(buffer,"HIJO: Soy el proceso %d\n",getpid());
			write(1,buffer,strlen(buffer));

			/* Probamos si tenemos acceso desde una función */	
			Escribe_variables();

			/* Termina su ejecución */
			exit(0);

		case -1: /* Se ha producido un error */
			sprintf(buffer,"Se ha prodcido une error\n");
			write(1,buffer,strlen(buffer));
			break;

		default: /* Escribe aqui el codigo del padre */
			sprintf(buffer,"PADRE: Soy el proceso %d\n",getpid());
			write(1, buffer, strlen(buffer));
	
			/* Probamos si tenemos acceso desde una función */	
			Escribe_variables();
	}
	sprintf(buffer,"Solo lo ejecuta el padre: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));

	return 0;
}
