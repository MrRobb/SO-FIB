#include <unistd.h>
#include <stdio.h>
#include <string.h>

main(){
int numero = 10562;
int nbytes,ret;
char buff[80];
char strnum[6];

nbytes = sizeof(int);
sprintf(buff, "Entero en representacion interna. Voy a escribir %d bytes:\n", nbytes);
write(1,buff,strlen(buff));
write(1, &numero, nbytes);

write(1,"\n", sizeof(char));

sprintf(strnum,"%d", numero);
nbytes = strlen(strnum);
sprintf(buff, "Entero en formato string. Voy a escribir %d bytes:\n", nbytes);
write(1,buff,strlen(buff));

write(1, strnum, nbytes);
write(1,"\n", sizeof(char));

}
