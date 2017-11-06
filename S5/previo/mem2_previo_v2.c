#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


/* readint - Devuelve un entero leido desde teclado */
int readint(void)
{
	char buff[100];
	int x;
	x = read (0, &buff, sizeof(buff));
	if (x < 0) {
		perror (" ERROR leyendo numero ");
		exit (0);
	}
	buff[x-1] = '\0'; //substituir \n por \0
	x = atoi (buff);
	return x;
}

void fillvector (int *vector, int num_elems)
{
	int i;
	for (i=0; i<num_elems; i++) {
		vector [i] = i;
	}
}

int *vector;

int
main (int argc, char *argv[])
{
  int i;
  int n;
  int s=0;
  char buff[100];

  if (argc != 1)
    {
      sprintf (buff, "Usage: %s \n", argv[0]);
      write (2, buff, strlen(buff));
      exit (1);
    }
  sprintf (buff, "Soy el proceso %d\n", getpid());
  write (1, buff, strlen(buff));

  sprintf (buff, "Introduce el numero de elementos del vector y pulsa Return:");
  write (1, buff, strlen(buff));
  n = readint ();

  vector = sbrk(n * sizeof(int));
  fillvector (vector, n);

  for (i=0; i<n; i++) {
	s += vector[i];
  }
  sprintf (buff, "la suma de los %d elementos del vector es %d\n", n, s);
  write (1, buff, strlen(buff));

  sprintf (buff, "Pulsa Return para acabar la ejecución\n");
  write (1, buff, strlen(buff));
  read(0, buff, 1);
  exit (0);
}
