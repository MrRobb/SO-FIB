#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void error_y_exit(char* msg,int exitStatus) {
	perror(msg);
	exit(exitStatus);
}

void muta_cat() {
	execlp("cat","cat",NULL);
	error_y_exit("a fallado la mutacion\n",1);
}

int main() {
	char buf[256];
	int pf[2];
	if(pipe(pf) == -1) error_y_exit("a fallado la creacion del pipe\n",1);
	int pid = fork();
	if(pid == 0) { //hijo
		dup2(pf[0],0);
		close(pf[0]);close(pf[1]);
		muta_cat();
	}
	else { //padre
		close(pf[0]);
		sprintf(buf,"inici\n");
		write(pf[1],buf,strlen(buf));
		close(pf[1]);
		waitpid(-1,NULL,0);
		sprintf(buf,"fin\n");
		write(1,buf,strlen(buf));
	}
}

