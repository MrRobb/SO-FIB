#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 256

main(){
char buffer[BUFF_SIZE];
char *buf="fin ejecución\n";
int ret;
	ret=read(0, buffer, BUFF_SIZE);
	while(ret>0){
		write(1, buffer, ret);
		ret=read(0, buffer, BUFF_SIZE);
	}
	write(1, buf, strlen(buf));
}
