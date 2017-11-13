# Entrada / Salida

- Entrada: exterior -> proceso
- Salida: proceso -> exterior

Lo que queremos es abstraer toda la complejidad del acceso a los datos de entrada y salida a una interfaz simple y sencilla.

> Pasar de puertos (registros de control, de estado...) a _cin_ y _cout_

Desafortunadamente, en medio de estás cosas está:

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
- **0 -> stdin (input)** // teclado
- **1 -> stdout (output)** // pantalla
- **2 -> stderror (errores)** // pantalla

Permiten redireccionamiento, vamos que cuando haces:
```
./mi_programa > fichero
```
Redireccionas el canal 1 al fichero
```
./mi_programa < fichero
```
Redireccionas el canal 0 al fichero

Por eso en el write ponemos:
```c
write(1, ...); // escribir en stdout
```

Quien dice qué números corresponden a qué dispositivos, lo maneja el nivel lógico.

> Los dispositivos son ficheros, bueno, no exactamente, los dispositivos se tratan como ficheros, para poder leer o escribir de/en ellos.

#### Lógico

Aporta:
> Compartición de dispositivos (accesos concurrentes al mismo dispositivos, da orden)

Enlaza dispositivo virtual y dispositivo (físico)

Manipula bloques de datos de medida la que quieras.

Cuando haces:
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

![dispositivo]()

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
struct file_operations fops_drive_1 = {
    owner: THIS_MODULE,
    read: read_drive_1
}; // Estructura que define las operaciones que soporta el driver

int read_drive_1 (struct file* file, char user* buffer, size_t s, loff_t *off) {
    ...
    return size;
}

// Completar...
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

// Completar...

### Sistema de ficheros

#### Tipos de ficheros
