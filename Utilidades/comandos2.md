

COMANDOS
========

Sessió 7: Gestió d'Entrada / Sortida
------------------------------------


**mknod:** Comando que crea un fichero especial

> mknod - make block or character special files
```c
mknod** [OPTION]... NAME TYPE [MAJOR MINOR]
```
>  Create the special file NAME of the given TYPE.

>- c: create a character (unbuffered) special file
>- p: create a FIFO

**insmod:** Comando que inserta un módulo en el kernel
> insmod — simple program to insert a module into the Linux Kernel
```c
insmod [filename] [module options ...]
```
> insmod  is a trivial program to insert a module into the kernel: if the filename is a hyphen, the module is taken  from  standard  input. 
> Only the most general of error messages are reported.

**rmmod:** Comando que descarga un módulo del kernel
> rmmod — simple program to remove a module from the Linux Kernel
```c
rmmod [-f] [-w] [-s] [-v] [modulename]
```
> rmmod  is  a  trivial program to remove a module (when module unloading support is provided) from the kernel. 

**lsmod:** Comando que muestra el estado de los módulos cargados en el kernel
> lsmod — program to show the status of modules in the Linux Kernel
```c
lsmod
```
> lsmod  is  a  trivial  program which nicely formats the contents of the */proc/modules*, showing what kernel modules are currently loaded.

**sudo:** Comando que permite ejecutar un comando como root
> sudo, sudoedit - execute a command as another user

```c
sudo [-D level] -h | -K | -k | -V

sudo -v [-AknS] [-D level] [-g group name|#gid] [-p prompt] [-u user name|#uid]

sudo -l[l] [-AknS] [-D level] [-g group name|#gid] [-p prompt] [-U user name] [-u user name|#uid] [command]

sudo [-AbEHnPS] [-C fd] [-D level] [-g group name|#gid] [-p prompt] [-u user name|#uid] [VAR=value] [-i | -s] [command]

sudoedit [-AnS] [-C fd] [-D level] [-g group name|#gid] [-p prompt] [-u user name|#uid] file ...
```
>  sudo allows a permitted user to execute a command as the superuser or another user, as specified by the security policy.  The real and effective uid and gid are set to match those of the target user, as specified in the password database, and the group vector is initialized based on the group database (unless the -P option was specified).


**open:** Abre un fichero o dispositivo

> open, creat - open and possibly create a file or device
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
```
>  Given a pathname for a file, open() returns a file descriptor, a small, nonnegative integer  for  use  in  subsequent  system  calls  (read(2), write(2), lseek(2), fcntl(2), etc.).  The file descriptor returned by a successful  call  will  be  the  lowest-numbered  file  descriptor  notcurrently open for the process.

**write:** Llamada a sistema para escribir en un dispositivo virtual
> write - write to a file descriptor
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```
> write()  writes  up  to  count bytes from the buffer pointed buf to the file referred to by the file descriptor fd.
> On success, the number of bytes written  is  returned  (zero  indicates nothing  was  written).   On  error,  -1  is returned, and errno is set appropriately.

**read:** Llamada a sistema para leer de un dispositivo virtual
>  read - read from a file descriptor
```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```
> read()  attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.
> On success, the number of bytes read is returned (zero indicates end of file), and the file position is advanced by this number.  It is not  an error  if  this  number  is smaller than the number of bytes requested; this may happen for example because fewer bytes are actually  available right  now  (maybe  because we were close to end-of-file, or because we are reading from a pipe, or from a terminal),  or  because  read()  was interrupted  by  a  signal.  On error, -1 is returned, and errno is set appropriately.  In this case it is left unspecified  whether  the  file position (if any) changes.

**grep:** Comando que busca patrones en un fichero o en -c su entrada estándar si no se le pasa fichero como
parámetro
> grep - search a file for a pattern
```c
grep [-E| -F][-c| -l| -q][-insvx] -e pattern_list...[-f pattern_file]...[file...]
grep [-E| -F][-c| -l| -q][-insvx][-e pattern_list]...-f pattern_file...[file...]
grep [-E| -F][-c| -l| -q][-insvx] pattern_list[file...]
```
> The grep utility shall search the input files, selecting lines matching one or more patterns; the types  of  patterns  are  controlled  by  the options  specified.  

>- -c: Write only a count of selected lines to standard output.

**ps:** Comando que muestra información sobre los procesos en ejecución
> ps - report a snapshot of the current processes.
```c
ps [options]
```
> ps displays information about a selection of the active processes.
> 
>- -e: Select all processes. Identical to -A.
>- -o: format       
> User-defined format.
> format is a single argument in the form of a blank-separated or comma-separated list, which offers a way to specify individual output columns. 

**strace:** Lista las llamadas a sistema ejecutadas por un proceso
> strace - trace system calls and signals
```c
strace [-CdffhiqrtttTvxx] [-acolumn] [-eexpr] ... [-ofile] [-ppid] ... [-sstrsize] [-uusername] [-Evar=val] ... [-Evar] ... [command [arg...]]
strace -c [-eexpr] ... [-Ooverhead] [-Ssortby] [command [arg...]]
```
> In the simplest case strace runs the specified command until it  exits.  It  intercepts  and  records  the  system  calls  which are called by a process and the signals which are received by a process. 
> 
>- -e:  expr    
>  A  qualifying expression which modifies which events to trace or how to trace them.  The  format  of  the expression is: `[qualifier=][!]value1[,value2]...` where  qualifier  is  one of trace, abbrev, verbose, raw,  signal,  read,  or  write  and  value   is   a qualifier-dependent  symbol  or number.  The default qualifier  is  trace.   Using  an  exclamation  mark negates  the  set  of  values.  For example, -e open means literally -e trace=open which  in  turn  means trace  only  the  open  system  call.   By contrast, -e trace=!open means  to  trace  every  system  call except  open.  In  addition, the special values all and none have the obvious meanings.
>- -c: Count  time,  calls, and errors for each system call nd report a summary on  program  exit.  On  Linux,  this  attempts  to  show system time (CPU time spent running in the kernel)  independent  of  wall  clock time.   If  -c  is  used with -f or -F (below), only aggregate totals for all traced processes are kept.
