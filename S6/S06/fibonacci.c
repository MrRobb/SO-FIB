#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long fibonacci(unsigned i) {
	if (i == 0) return 0;
	if (i == 1) return 1;
	return fibonacci(i-1) + fibonacci(i-2);
}

void usage() {
	char buffer[80];

	strcpy(buffer,"fib n\n");
	write(1,buffer,strlen(buffer));
	exit(1);
}
void main(int argc,char *argv[]) {
	unsigned n;
	long f;
	char buffer[80];
	
	if (argc != 2) usage();
	n = atoi(argv[1]);
	f = fibonacci(n);
	sprintf(buffer,"El fibonacci de %u es %ld\n",n,f);
	write(1, buffer, strlen(buffer));
}
	
