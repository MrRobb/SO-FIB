#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void error_y_exit(char* msg,int error_status) {
	perror(msg);
	error(error_status);
}

int main() {
	char c[1];
	int fp = open("pipeAB",O_RDONLY);
	if(fp == -1) error_y_exit("error en abrir la pipe",1);
	while(read(fp,c,1) > 0) {
		write(1,c,1);	
	}
	close(fp);
}
