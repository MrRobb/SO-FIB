#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define REGION_SIZE		4096

int *p;

void funcion_segmentation(int s)
{
	printf("ERROR DE MEMORIA\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	char buff[256];					

	struct sigaction sa;
	sa.sa_handler = &funcion_segmentation;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGSEGV, &sa, NULL);

	sprintf( buff, "Addresses:\n");
	write(1, buff, strlen(buff));	
	sprintf( buff, "\tp: %p\n", &p);
	write(1, buff, strlen(buff));	

	*p = 5;

	sprintf( buff, "\tp Address: %p, p value: %p, *p: %d\n", &p, p, *p);
	write(1, buff, strlen(buff));	

	exit(0);

}