#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[])
{
	int pipefd[2];
	int cpid;
	char buff;

	if(pipe(pipefd) == -1)
	{
		perror("Error creating a pipe.\n");
		exit(1);
	}

	cpid = fork();

	if(cpid == -1)
	{
		perror("Error on fork.\n");
		exit(1);
	}
	else if(cpid == 0)
	{
		close(0);
		dup(pipefd[0]);

		close(pipefd[0]);
		close(pipefd[1]);

		execlp("cat", "cat", (char*)NULL);

		perror("Error on execlp.\n");
		exit(1);
	}
	else
	{
		char buff2[80];
		sprintf(buff2, "Inicio\n");
		write(pipefd[1], &buff2, strlen(buff2));

		close(pipefd[1]);

		int exit_status;
		waitpid(-1, &exit_status, 0);

		sprintf(buff2, "Fin\n");
		write(1, buff2, strlen(buff2));
	}
}

