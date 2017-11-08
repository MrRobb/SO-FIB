#include <unistd.h>
#include <string.h>
#include <stdio.h>

// Este codigo escribe todos los bytes que lee de la entrada std en la salida stda

main(){
	char *buf="fin ejecuci贸n\n";
    int ret;
    char buffer[256];
    ret=read(0,&buffer,sizeof(buffer));
    while(ret>0)
    {
        write(1,&buffer,strlen(buffer));
        ret=read(0,&buffer,sizeof(buffer));
    }
    write(1,buf,strlen(buf));
}
