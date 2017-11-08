#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


void error_y_exit(char* msg,int error_status) {
	perror(msg);
	exit(error_status);
}

int main() {
	char buf[256];
	int f = creat("salida.txt",O_CREAT|O_TRUNC|0600);
	if(f == -1) error_y_exit("error en crear el archivo",1);
	sprintf(buf,"ABCD");
	write(f,buf,strlen(buf));
}
