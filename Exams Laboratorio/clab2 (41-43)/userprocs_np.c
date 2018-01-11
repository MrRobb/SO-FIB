#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/********************************************************************
Si descomentais las 3 líneas "kill(getpid(),SIGSTOP);"
podreis ver en el /proc las configuraciones de las tablas de canales y como se han
hecho las redirecciones de los canales estandar hacia las pipes. Por ejemplo:

millanva@AMV-Desktop:~$ ll /proc/984/fd    --PADRE
total 0
dr-x------ 2 millanva millanva  0 dic 19 20:34 ./
dr-xr-xr-x 9 millanva millanva  0 dic 19 20:34 ../
lrwx------ 1 millanva millanva 64 dic 19 20:34 0 -> /dev/pts/8
lrwx------ 1 millanva millanva 64 dic 19 20:34 1 -> /dev/pts/8
lrwx------ 1 millanva millanva 64 dic 19 20:34 2 -> /dev/pts/8
lr-x------ 1 millanva millanva 64 dic 19 20:34 3 -> /home/millanva/Escritorio/SO/wc2parent.fifo|

millanva@AMV-Desktop:~$ ll /proc/985/fd    --HIJO PS
total 0
dr-x------ 2 millanva millanva  0 dic 19 20:34 ./
dr-xr-xr-x 9 millanva millanva  0 dic 19 20:34 ../
lrwx------ 1 millanva millanva 64 dic 19 20:34 0 -> /dev/pts/8
l-wx------ 1 millanva millanva 64 dic 19 20:34 1 -> pipe:[84033]
lrwx------ 1 millanva millanva 64 dic 19 20:34 2 -> /dev/pts/8

millanva@AMV-Desktop:~$ ll /proc/986/fd    --HIJO GREP
total 0
dr-x------ 2 millanva millanva  0 dic 19 20:34 ./
dr-xr-xr-x 9 millanva millanva  0 dic 19 20:34 ../
lr-x------ 1 millanva millanva 64 dic 19 20:34 0 -> pipe:[84033]
l-wx------ 1 millanva millanva 64 dic 19 20:34 1 -> pipe:[84034]
lrwx------ 1 millanva millanva 64 dic 19 20:34 2 -> /dev/pts/8

millanva@AMV-Desktop:~$ ll /proc/987/fd    -- HIJO WC
total 0
dr-x------ 2 millanva millanva  0 dic 19 20:34 ./
dr-xr-xr-x 9 millanva millanva  0 dic 19 20:34 ../
lr-x------ 1 millanva millanva 64 dic 19 20:35 0 -> pipe:[84034]
l-wx------ 1 millanva millanva 64 dic 19 20:35 1 -> /home/millanva/Escritorio/SO/wc2parent.fifo|
lrwx------ 1 millanva millanva 64 dic 19 20:34 2 -> /dev/pts/8


**************************************************************************************/

void
error_y_exit (char *str)
{
    perror (str);
    exit (EXIT_FAILURE);
}

void
Usage ()
{
    char buffer[256];
    sprintf (buffer, "USAGE: userprocs username\n");
    write (1, buffer, strlen (buffer));
    exit (EXIT_FAILURE);
}

int
main (int argc, char *argv[])
{

    // Pipes
    int   ps2grep[2];
    int   grep2wc[2];

    int   read_wc2parent
    int   write_wc2parent;
    int   ret;

    // Buffers
    char  wcbuffer[256];
    char  buffer[256];


    if (argc != 2)
        Usage ();

    if (pipe(ps2grep) < 0 || pipe(grep2wc) < 0)
        error_y_exit("Error --> pipe")

    ret = mknod ("wc2parent.fifo", S_IFIFO | 0666, 0);	// Creo la NAMED-PIPE, control de EEXIST
    if ((ret == -1) && (errno != EEXIST))
        error_y_exit ("Creando la named pipe");

    switch (fork ())		//fork para mutar a ps
    {
        case -1:
        error_y_exit ("Fork para ps");
        break;
        case 0:
        dup2 (ps2grep[1], 1);
        close (ps2grep[1]);	//redirecció Salida Estandar a pipe. Cierre canal duplicado.


        close (ps2grep[0]);	//cierro canales de pipe que no uso
        close (grep2wc[0]);	//evitando bloqueos
        close (grep2wc[1]);

        //kill(getpid(),SIGSTOP);

        execlp ("ps", "ps", "-eaf", (char *) NULL);
        error_y_exit ("Mutación a ps");
        break;

    }

    switch (fork ())		//fork para mutar a grep
    {
        case -1:
        error_y_exit ("Fork para grep");
        break;
        case 0:
        dup2 (ps2grep[0], 0);
        close (ps2grep[0]);	//redirecció entrada Estandar a pipe. Cierre canal duplicado.

        dup2 (grep2wc[1], 1);
        close (grep2wc[1]);	//redirecció Salida Estandar a pipe. Cierre canal duplicado.

        close (ps2grep[1]);	//cierro canales de pipe que no uso
        close (grep2wc[0]);	//evitando bloqueos

        //kill(getpid(),SIGSTOP);

        execlp ("grep", "grep", argv[1], (char *) NULL);
        error_y_exit ("Mutación a grep");
        break;

    }

    switch (fork ())		//fork para mutar a wc
    {
        case -1:
        error_y_exit ("Fork para wc");
        break;
        case 0:
        dup2 (grep2wc[0], 0);
        close (grep2wc[0]);	//redirecció entrada Estandar a pipe. Cierre canal duplicado.

        write_wc2parent = open ("wc2parent.fifo", O_WRONLY, 0);
        dup2 (write_wc2parent, 1);
        close (write_wc2parent);	//redirecció Salida Estandar a named pipe. Cierre canal duplicado. Bloqueo de open

        close (ps2grep[0]);
        close (ps2grep[1]);	//cierro canales de pipe que no uso
        close (grep2wc[1]);	//evitando bloqueos

        //kill(getpid(),SIGSTOP);

        execlp ("wc", "wc", "-l", (char *) NULL);
        error_y_exit ("Mutación a wc");
        break;

    }

    ///PADRE
    //Cierro los canales de pipe que no uso
    close (grep2wc[0]);
    close (grep2wc[1]);
    close (ps2grep[0]);
    close (ps2grep[1]);

    read_wc2parent = open ("wc2parent.fifo", O_RDONLY, 0);	//abre la named-pipe. Hay bloqueo

    while ((ret = read (read_wc2parent, wcbuffer, 256)) > 0)	//la lectura se bloquea hasta que wc acaba
    {
        wcbuffer[ret - 1] = '\0';
        sprintf (buffer,
            "El usuario %s está ejecutando %s procesos\n", argv[1],
            wcbuffer);
            write (1, buffer, strlen (buffer));
        }

        close (read_wc2parent);
        while (waitpid (-1, NULL, 0) > 0);


    }
