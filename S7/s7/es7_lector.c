#include <unistd.h>
#include <stdio.h>

main(){
int numero;
int fd;

read(0, &numero, sizeof(int));

printf("%d \n",numero);

}
