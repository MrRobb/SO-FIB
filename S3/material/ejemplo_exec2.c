#include <stdio.h>
#include <unistd.h>
#include <string.h>

main(){

char buffer[80];

sprintf(buffer, "Soy el proceso: %d\n", getpid());
write(1,buffer,strlen(buffer));

execlp("./ejemplo_fork1", "ejemplo_fork1", (char *) 0);

strcpy(buffer, "Después del exec\n");
write(1,buffer,strlen(buffer));

}
