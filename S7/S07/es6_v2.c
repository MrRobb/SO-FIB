#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

void interrupcion(int s)
{
	char buff[80];
	sprintf(buff, "SIGINT recibido\n");
	write(1, buff, strlen(buff));
}

main(){
	// Interrupt systems calls
	//siginterrupt(SIGINT, 1);
	signal(SIGINT, interrupcion);

	char c;
	int ret;

	ret = read(0, &c, sizeof(char));

	char buff[80];
	if(ret >= 0)
		sprintf(buff, "read correcto!\n");
	else
	{
		if(errno == EINTR)
			sprintf(buff, "read interrumpido por signal\n");
		else
			sprintf(buff, "read incorrecto\n");
	}

	write(1, buff, strlen(buff));
}
