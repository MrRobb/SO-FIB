#include <unistd.h>

main(){
int numero = 10562;
int fd;

write(1, &numero, sizeof(int));

}
