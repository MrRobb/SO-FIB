#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
 
main(int argc, char *argv[])
{
    if (argc != 3) printf ("Usage(): ./insertarx2 input position \n");
    else
    {
        char buff[32];
        sprintf(buff, "X");
        char buff2[32];
        int fd = open(argv[1], O_RDWR);
        int final = lseek(fd,0,SEEK_END);
        int i = atoi(argv[2]);
         
        while (i != final)
        {
            lseek(fd, i, SEEK_SET);
            read(fd, &buff2, 1);
            lseek(fd, i, SEEK_SET);
            write(fd, &buff, 1);
            sprintf(buff, "%s", buff2);
            ++i;
        }
        close(fd);
    }
}
