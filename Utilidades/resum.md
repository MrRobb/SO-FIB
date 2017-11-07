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
