# PROCESOS

**PID**: Identificador único del proceso. Se usa en llamadas del sistema.

**Credenciales**: userID y groupID. Determina los derechos de acceder a recursos del sistema y ficheros.

## Gestión de Procesos

Cuando un proceso crea a otro, todo se organiza en estructura de árbol.

Cada proceso tiene su PID pero además también tiene el PPID para identificar a su padre.

El sistema operativo decide los recursos que comparte, su planificación y su espacio de direcciones.

### Syscall

UNIX --> padre e hijo se ejecutan concurrentemente (a la vez), se duplica el código, la pila y los datos del padre y se le asignan al hijo.
- fork -> crea un nuevo proceso (si es el hijo, devuelve 0, si es el padre, devuelve el PID del hijo)
- exec -> muta a otro programa (cambia el espacio de direcciones)
- exit -> termina el proceso
- wait / waitpid -> espera a que muera un proceso (esto bloquea el proceso: RUN -> BLOCKED / WAITING)
- getpid -> te da el PID
- getppid -> te da el PPID

### Hereda

- Código, datos, pila
- Programación de signals
- Dispositivos virtuales (?)
- userID y groupID
- variables de entorno

### NO Hereda

- PID, PPID
- Contadores internos
- Alarmas y signals pendientes

### Muerte

Si quieres sincronizar el padre con la muerte del hijo haces que el padre espere su muerte con:

```c
pid_t pid = fork();
int status = 0;
waitpid(pid, &status, 0);

// Si quieres más info sobre waitpid mira el archivo comandos.txt
// que hay en la carpeta de Utilidades (SESIÓN 4)
```

Mientras el padre no haga waitpid no se libera el espacio que ocupa el PCB del hijo muerto (ESTADO ZOMBIE). Si el padre muere sin liberar los PCB's de sus hijos el sistema los libera (proceso init).

### Mutación

Si queremos mutar a otro programa, se usa el comando execlp.

> Si quieres más info sobre execlp mira el archivo comandos.txt que hay en la carpeta de Utilidades

Execlp cambia todo el contenido del espacio, pero se mantiene la identidad del proceso.

# EJEMPLOS

### FORK

```c   
int ret = fork();

if (ret == 0) {
    // HIJO
}

else if (ret < 0) {
    // ERROR
}

else {
    // PADRE
    // ret == pid del hijo
}
```

### ESQUEMA SECUENCIAL

Hasta que el hijo no acaba, el padre no crea otro proceso (porque se queda bloqueado en el waitpid esperando a que su hijo muera).

```c
#define NUM_PROCESOS 2
int ret;
for (int i = 0; i < NUM_PROCESOS; i++)
{
    ret = fork();

    if (ret < 0)
        control_error();

    else if (ret == 0) {
        // HIJO
        exit(0);
    }

    else {
        // PADRE
        waitpid(-1, NULL, 0);
    }
}
```

### ESQUEMA CONCURRENTE

El padre crea todos los procesos hijos que se ejecutan a la vez y después espera a que acaben todos.

```c
#define NUM_PROCESOS 2
int ret;

for (int i = 0; i < NUM_PROCESOS; i++)
{
    ret = fork();

    if (ret < 0)
        control_error();

    else if (ret == 0) {
        // HIJO
        exit(0);
    }
}

while (waitpid(-1, NULL, 0) > 0);
```

### CREAR 2^n PROCESOS

```c
#define N 10

for(int i = 0; i < N; i++)
{
    fork();
    printf("Hello World. I'm %d\n", getpid());
}
```

### MIRAR EL EXIT_STATUS

```c
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void tratar_exit_code(int status)
{
    if (WIFEXITED(status))
    {
        // Ha terminado por culpa de un exit
        int exitcode = WEXITSTATUS(status);
        printf("Ha terminado por un exit con exit_code: %d\n", exitcode);
    }

    else {
        // Ha terminado por un signal
        int signalcode = WTERMSIG(status);
        printf("Ha terminado con un signal con signal_code: %d\n", signalcode);
    }
}

int main(int argc, char const *argv[]) {
    for (int i = 0; i < 10; ++i)
    {    
        // FORK
        int ret = fork();

        // HIJO
        if (ret == 0)
        {
            exit(i);
        }

        // PADRE
        int status;
        waitpid(-1, &status, 0);
        tratar_exit_code(status);
    }
    return 0;
}
```
