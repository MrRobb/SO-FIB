# Entrada / Salida

- Entrada: exterior -> proceso
- Salida: proceso -> exterior

Lo que queremos es abstraer toda la complejidad del acceso a los datos de entrada y salida a una interfaz simple y sencilla.

> Pasar de puertos (registros de control, de estado...) a _cin_ y _cout_

Desafortunadamente, en medio de estas cosas está:

```c
ssize_t write(int fildes, const void *buf, size_t nbyte);
ssize_t read(int fildes, void *buf, size_t nbyte);
```

Básicamente, leer y escribir.

### Tipos de dispositivos

Se organizan según:
- Tipo:
    - Lógico
    - Físico
    - de Red
- Velocidad de acceso
- Flujo de acceso
- Exclusividad de acceso
- ...

### ¿Qué queremos?

- Operaciones **uniformes**: usar las mismas llamadas al sistema para todos los dispositivos.
- Utilizar **dispositivos virtuales**: utilizar identificadores que se traducen luego
- **Redireccionamiento**: pipes (lo veremos luego)

### Principios de diseño

#### Virtual

Aporta:
> Independencia, trabaja con dispositivos virtuales

Trabajamos con canales, que son un número que representa un dispositivo:
- **0** -> stdin (input) `// teclado`
- **1** -> stdout (output) `// pantalla`
- **2** -> stderror (errores) `// pantalla`

Permiten redireccionamiento, vamos que cuando haces:
```c
./mi_programa > fichero   //Redireccionas el canal 1 al fichero

./mi_programa < fichero   //Redireccionas el canal 0 al fichero
```


Por eso en el write ponemos:
```c
write(1, ...); // escribir en stdout
```

Quien dice qué números corresponden a qué dispositivos, lo maneja el nivel lógico.

> Los dispositivos son ficheros, bueno, no exactamente, los dispositivos se tratan como ficheros, para poder leer o escribir de/en ellos.

#### Lógico

Aporta:
>- Compartición de dispositivos (accesos concurrentes al mismo dispositivos, da orden)

Enlaza dispositivo virtual y dispositivo (físico)

Manipula bloques de datos de medida la que quieras.

Si haces el siguiente código:
```c
int canal = open("path_a_la_impresora");
write(canal, "hola\n", 5);
```
En canal se te guarda el número del cual tu puedes hacer write y se mandaría a la impresora.

> Se tienen en cuenta los permisos, ya que se accede como si fuese un fichero

#### Físico

Aporta:
> Implementación a bajo nivel, traduce los parámetros lógicos a parámetros concretos.

1. Inizializa el dispositivo
2. Mira si está libre
3. Hace la programación de la operación que se le pide
4. espera o no a que termine
5. Devuelve los resultados o informa de algún error

Lo dispositivo se identifican con:
- Tipo: **block/character**
- **Major** -> indica el tipo de dispositivo
- **Minor** -> instáncia concreta según el major

### Drivers

#### Nivel Físico
**Aumentan la funcionalidad** del sistema operativo.

Con el **MAJOR** y el **MINOR** (son int) identifican el dispositivo dentro del kernel.

![dispositivo](https://github.com/MrRobb/SO-FIB/blob/master/Utilidades/img%20resum/img13.png)

#### Nivel Lógico

```c
open(nombre);
```
El nombre del open, se lo va a dar el sistema lógico, ya que este asocia el nombre al dispositivo (con la syscall mknod).

> [man mknod](http://www.tldp.org/pub/Linux/docs/ldp-archived/system-admin-guide/translations/es/html/ch05s02.html)

**mknod** genera el **file descriptor**: Es el número que le pones al write.

Normalmente se hace:
```c
int fd = open("path_al_fichero");
write(fd, "hola\n", 5);
close(fd);
```

Para añadir un dispositivo nuevo puedes:
- **Recompilar el kernel**
- Añadir dispositivos **sin recompilar (solo si es sistema lo permite)**

#### Estructura

```c

// Estructura que define las operaciones que soporta el driver
struct file_operations fops_drive_1 = {
    owner: THIS_MODULE,
    read: read_drive_1
};

//En este caso, solo operacion lectura (read)
int read_drive_1 (struct file* file, char user* buffer, size_t s, loff_t *off) {
    ...
    return size;
}

//Operaciones para cargar/eliminar el driver del kernel
static int _init driver1_init(void) {
  ...
}
static void _exit driver1_exit(void){
  ...
}

//Operaciones del módulo de cargar/eliminar el driver del kernel
module_init(driver1_init);
module_exit(driver1_exit);
```

#### Contenido del DD (Device Driver)
- **Información general** del DD (nombre, autor...)
- Implementación de las **funciones genéricas**
    - open
    - read
    - write
    - ...
- Funciones de **inicialización**
- Funciones de **desinstalación**

#### Pasos a seguir

##### Físico
- Compilar el DD en ```.ko```
- **Instalar las rutinas** del driver (se decide el major y minor)

##### Lógico
- Crear un dispositivo lógico (con mknod)

##### Virtual
- Crear el dispositivo virtual (con open)

### Pipe

Implementa un **buffer temporal** con funcionamiento FIFO. **Los datos de la pipe se borran a medida que se leen**.

Sirven para **compartir información** entre procesos.

- Pipe **sin nombre**, solo accesible via herencia
- Pipe **con nombre**, cualquiera que tenga permiso puede acceder al dispositivo


### Socket

// TO-DO: completar...

### Sistema de ficheros

#### Tipos de ficheros

#### Estructuras ... (se las salta)

#### Llamadas al sistema

- Escribir por pantalla -> no bloqueante
- Escribir una pipe -> no bloqueante

- Escribir al disco -> bloqueante

![Llamadas al sistema](https://github.com/MrRobb/SO-FIB/blob/master/Utilidades/img%20resum/img14.png)

### OPEN

```c
int fd = open("path_al_fichero", modo_de_acceso, [flags]);
/*
Path -> dirección al fichero
Modo de acceso:
    - O_RDONLY -> solo lectura
    - O_WRONLY -> solo escritura
    - O_RDWR -> lectura y escritura
*/
```

##### Creación:
>- ficheros especiales tienen que existir antes de acceder a ellos
>- especificar los `permision_flags` (or de S_IRWXU, S_IRUSR...)
>- crear -> añadir O_CREAT (con or de bits) en acces_mode
>- no hay llamada pera eliminar algunos datos de un fichero, solo podemos borrarlos todos.
>- cortar el contenido de un fichero: O_TRUNC

```c
//si no exixtia, lo crea
open(“X”,O_RDWR|O_CREAT, S_IRUSR|S_IWUSR)

//si no existia, lo crea. else, libera datos y tamaño = 0;
open(“X”,O_RDWR|O_CREAT|O_TRUNC, S_IRWXU)
```
##### Estructuras de datos

```c
Open (cont);
```
> **Def** Efecto sobre estructuras de datos internas del sistema.
>- Ocupa un canal libre de TC. (1º disponible)
>- Ocupa una nueva entrada de TFO: (Pos L/E=0)
>- Asocia las estructuras al DD que le toca (major del nombre simbólico).
>- diferentes TFO pueden apuntar al mismo DD


![Estructuras de datos](https://github.com/MrRobb/SO-FIB/blob/master/Utilidades/img%20resum/img15.png)

### READ

```c
int fd = open(...);
char buffer[64] // del tamaño que quieras
int num_bytes_leidos = read(fd, buffer, num_bytes_a_leer); // bytes a leer que quieras
```

- Pide la lectura de num_bytes_a_leer:
    - Si hay suficientes --> los lee.
    - Si hay menos de los que pide --> lee los que hay.
    - Si no hay nada que se puede leer -> depende del dispositivo (se bloquea, o devuelve 0)

- Devuelve:
    - **0** --> no hay nada que leer
    - **> 0** --> los bytes leídos
    - **-1** --> error

- La posición por la cual debería seguir leyendo después, se avanza automáticamente (lo hace el kernel) tantas posiciones como bytes haya leído

### WRITE

```c
n = write(fd, buffer, count);
```
>- **n:** num de bytes escritos
>- **fd:** num del canal
>- **buffer:** puntero de memoria de donde copiar los datos
>- **count:** num de bytes a esctibir

Funcionamiento:
> Pide la escritura de count chars al dispositivo asociado a fd.
>- Si hay espacio para count -> escribe count.
>- Si hay menos que count -> escribe los que quepan.  
>- Si no hay espacio -> depende de dispositivo (bloqueo, return 0, ...).

> La posicion l/e avanza automáticamente (kernel en write) tantas posiciones como bytes escritos
> `Posición_l/e = posición_l/e + num_bytes_escritos`

Devuelve:
- **-1** --> si hay error
- **>= 0** --> Los bytes que ha escrito realmente

- La posición por la cual debería seguir escribiendo después, se avanza automáticamente (lo hace el kernel) tantas posiciones como bytes haya escrito.

### DUP

```c
newfd = dup(fd);
```

**Hace una copia del canal que le pases como parámetro.**

Hace la copia en la primera entrada libre de la Tabla de Canales. Se comparten los punteros de lectura y escritura, es decir, si yo escribo algo en fd, si luego sigo escribiendo en newfd continuará por donde lo he dejado con fd (no se sobreescribe).

**Devuelve:**
- **-1** --> error
- **> 0** --> canal nuevo


### DUP2

```c
newfd = dup2(fd, newfd);
```

**Cierra el canal newfd si estaba abierto y se duplica el canal fd en newfd.**

Lo hace de forma atómica (en una sola instrucción), eso significa que:
```c
dup2(viejo, nuevo);
```
es diferente de
```c
close(nuevo);
nuevo = dup(viejo);
```
Ya que dup2 es una sola instrucción. Siempre hace las dos cosas o no hace ninguna.

### CLOSE

```c
close(fd);
```

- Se elimina el canal fd de los niveles inferiores
- Es posible que haya varias referencias al canal por lo tanto cuando haces close el contador de referencias se decrementa por 1. Lo mismo para la lista de inodos.
- Si el número de referencias es 0, se elimina de la Tabla de Ficheros Abiertos, lo mismo en la Tabla de Inodos.


TO-DO: completar

### Pipe

TO-DO: completar
