#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
 
main(int argc, char *argv[])
{
    if (argc == 1) printf("Usage(): ./append file \n");
    else
    {
            char buff[128];
            int fd = open(argv[1], O_RDONLY);
            int fd2 = open(argv[1], O_WRONLY);
            if (fd == -1 || fd2 == -1) perror("Error en open");
        lseek (fd, 0, SEEK_SET);
            int fi = lseek(fd2, 0, SEEK_END);
            while (fi != 0)
            {
                read(fd,buff,1);
                write(fd2,buff,1);
                --fi;               
            }
            close(fd);
            close(fd2);
    }
}
