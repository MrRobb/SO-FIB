#include <stdio.h>
#include <unistd.h>
#include <string.h>

main(){

char buffer[80];

sprintf(buffer, "Soy el proceso: %d\n", getpid());
write(1,buffer,strlen(buffer));

execlp("ls", "ls", "-l", (char *) 0);

sprintf(buffer, "Soy el proceso: %d\n", getpid());
write(1,buffer,strlen(buffer));

}
