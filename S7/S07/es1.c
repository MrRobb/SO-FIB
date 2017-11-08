#include <unistd.h>
#include <string.h>

main(){
char c;
char *buf="fin ejecución\n";
int ret;
	ret=read(0,&c,sizeof(c));
	while(ret>0){
		write(1,&c,sizeof(c));
		ret=read(0,&c,sizeof(c));
	}
	write(1,buf,strlen(buf));
}
