#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_STRING 256

main(){
	char buffer[MAX_STRING];
	int value;
	char c;
	int ret;

	ret = read(0, &value, sizeof(value));
	while(ret >0){
		sprintf(buffer,"%d\n",value);
		write(1,buffer,strlen(buffer));
		ret = read(0,&c,sizeof(c));
		ret = read(0,&value, sizeof(value));
	}
}
