#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
 
main(int argc, char *argv[])
{
    char buff[32];
    char final[32];
    if (argc != 2) printf ("Usage(): ./invirtiendo_fichero.c filetoinvert\n");
    else
    {
        int fd = open(argv[1], O_RDONLY);
    sprintf(final, "%s.inv", argv[1]);
        int fd2 = creat(final, 0777);
        int fi = lseek(fd, 0, SEEK_END);
        lseek(fd2, 0, SEEK_SET);
        while (fi-1 != 0)
        {
            lseek(fd, -2, SEEK_CUR);
            read(fd, buff, 1);
            write(fd2, buff, 1);
            --fi;       
        }
        close(fd);
        close(fd2);
    }
}
