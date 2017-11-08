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
	char buf1[256];
	char buf2[256];
	int fp = open("salida.txt", O_RDWR);
	if(fp == -1) error_y_exit("error en abrir el archivo",1);
	lseek(fp,-1,SEEK_END);
	read(fp,buf1,sizeof(char));//leemos de la posicion -1 para adelante(ultimo caracter)
	lseek(fp,-1,SEEK_CUR);//colocamos el puntero en la posicion que queremos
	sprintf(buf2,"X");
	
	write(fp,buf2,strlen(buf2));//colocamos la x en su lugar => ABCX
	write(fp,buf1,strlen(buf1));//colocamos el ultimo caracter => ABCXD
}
