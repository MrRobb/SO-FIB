#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void
suma (int op1, int op2, int *res)
{
  *res = op1 + op2;
}

int j;

int
main (int argc, char *argv[])
{
  int i;
  int *s;
  char buff[80];

  if (argc != 3)
    {
      sprintf (buff, "Usage: %s num1 num2\n", argv[0]);
      write(2,buff,strlen(buff));
      exit (1);
    }

  i = atoi (argv[1]);
  j = atoi (argv[2]);

  s = malloc(sizeof(int));
  suma (i, j, s);
  sprintf (buff, "suma de %d y %d es %d\n", i, j, *s);
  write(1,buff,strlen(buff));

  exit (0);
}