#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "utils.h"
#include <string.h>

#define NFORKS 50000

void do_nothing() {
	int i;
	i= 0;
}

main() {
	int pid, j, status;
	double start, stop;
	char buff[100];


	start= timersec();
	for (j=0; j<NFORKS; j++) {
		if((pid=fork())<0) {
			sprintf(buff, "Error in fork %dth \n",j);
			perror (buff);
			exit(0);
		}
		else if (pid ==0) {
			do_nothing();
			exit(0);
		}
		while(wait(&status)>0); 
	}
	stop=timersec();

	sprintf(buff, "%d processes created in %g sec.\n",NFORKS,stop-start);
	write (1, buff, strlen(buff));

	return 0;
}  

