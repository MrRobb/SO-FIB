#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE_BUFF 4

void imprime_buff(void *aux, int size)
{
	int i;
	char buffer[80];
	// Ya que "aux" es un tipo de datos void y por tanto nos permite
	// pasar cualquier tipo de datos debemos mantener una coherencia 
	// en el cast que se realice para usar dicho parámetro
	int *buff = (int *)aux;
	// Al ser un puntero, en C siempre podemos usarlo como un vector
	// EL compilador sabe que es un puntero a entero, por lo tanto 
	// calcula el tamaño de cada elemento
	sprintf(buffer, "Accedemos a traves de buff[i]\n");
	write(1, buffer, strlen(buffer) );
	for (i = 0; i < size; i++) {
		sprintf(buffer, "En la posicion %d hay %d\n", i, buff[i]);
		write( 1, buffer, strlen(buffer) );
	}

	// Y es lo mismo que hacer esto. Al ser un puntero el compilador no 
	// le suma 1, sino el tamaño de cada elemento
	// EL operados * accede a lo apuntado por el puntero, el contenido
	sprintf(buffer, "Accedemos a traves de *buff\n");
	write(1, buffer, strlen(buffer) );
	for (i = 0; i < size; i++) {
		sprintf(buffer, "En la posicion %d hay %d\n", i, *buff);
		write( 1, buffer, strlen(buffer) );
		buff++;
	}
}

int main(int argc, char *argv[])
{
	int a;			// a es un entero
	int buff_int[SIZE_BUFF];	//buff_int un vector de enteros
	int *pbuff_int;		//pbuff_int es un puntero a entero( o enteros) SIN INICIALIZAR
	char b;			// b es un caracter
	char *pb;		// pb es puntero a caracter SIN INICIALIZAR
	char buff_c[SIZE_BUFF];	// buff_c es un vector de carateres
	char buff[80];

	int i;

	// Inicializamos el vector
	for (a = 0; a < SIZE_BUFF; a++)
		buff_int[a] = a;

	// Accederemos a traves del puntero
	// esto es igual a pbuff_int=&buff_int[0], el compilador 
	// lo hace automatiamente, el simbolo & es para obtener la direccion
	// pero en el caso de los vectores no es necesario ponerlo
	pbuff_int = buff_int;

	// Comprobad que es lo mismo
	sprintf(buff, "Puntero %p buff_int=%p &buff_int[0]=%p\n", pbuff_int, buff_int, &buff_int[0]);
	write( 1, buff, strlen(buff) );
	sprintf(buff, "Usamos el puntero pbuff_int-------------------\n");
	write( 1, buff, strlen(buff) );
	imprime_buff((void *)pbuff_int, SIZE_BUFF);
	sprintf(buff, "Usamos el vector buff_int-------------------\n");
	write( 1, buff, strlen(buff) );
	imprime_buff((void *)buff_int, SIZE_BUFF);

	// Cuando los punteros no estan inicializados , podrian valer 
	// cualquier cosa, desde una direccion valida, de casualidad, a 0 
	// y provocar un fallo en el programa
	sprintf(buff, "Puntero sin inicializar pb=%p\n", pb);
	write( 1, buff, strlen(buff) );
	sprintf(buff, "Apuntamos a una zona segura pb=&b \n");
	write( 1, buff, strlen(buff) );
	pb = &b;
	b = 'H';
	sprintf(buff, "Puntero inicializado pb=%p, &b=%p b=%c *pb=%c\n", pb, &b, b, *pb);
	write( 1, buff, strlen(buff) );

	sprintf(buff, "Veamos como el compilador interpreta el tipo de los punteros....\n");
	write( 1, buff, strlen(buff) );
	sprintf(buff, "Los punt a enteros se incrementan en 4 y los de chars en 1 automaticamente\n");
	write( 1, buff, strlen(buff) );
	pb = buff_c;
	sprintf(buff, "ENTEROS\n");
	write( 1, buff, strlen(buff) );
	for (i = 0; i < SIZE_BUFF; i++) {
		sprintf(buff, "Direccion %d de buff de enteros %p\n", i, pbuff_int);
		write( 1, buff, strlen(buff) );
		pbuff_int++;
	}
	sprintf(buff, "CHARS \n");
	write( 1, buff, strlen(buff) );
	for (i = 0; i < SIZE_BUFF; i++) {
		sprintf(buff, "Direccion %d de buff de caracteres %p\n", i, pb);
		write( 1, buff, strlen(buff) );
		pb++;
	}

}
