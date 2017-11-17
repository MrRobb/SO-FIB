#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

char buff[256];
int interrupt_int = 0;

void tract_sigint(int s) {
	interrupt_int = 1;
}

main(){
	char c;
	int ret;

	struct sigaction sa;
	sa.sa_handler = &tract_sigint;
	sigfillset(&sa.sa_mask);
	sigaction(SIGINT,&sa,NULL);

	ret = read(0, &c, sizeof(char));
	if (interrupt_int == 1) {
		sprintf(buff,"read interrupido por signal\n");
		write(1, buff, strlen(buff));
	}
	else {
		write(1, c, strlen(c));
	}
}