#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


void func(int s) {
	char buf[256];
	sprintf(buf,"SIGINT recibido \n");
	write(1,buf,strlen(buf));
}

main(){
	char c;
	char buf[256];
	signal(SIGINT,func);
	//siginterrupt(SIGINT,1);
	int ret = read(0, &c, sizeof(char));
	if(ret > 0) sprintf(buf,"READ Correcto \n");
	else if(ret < 0) sprintf(buf,"%s \n",strerror(errno));
	else sprintf(buf,"READ con error \n");
	write(1, &buf, strlen(buf));
	write(1, &c, sizeof(char));

}
