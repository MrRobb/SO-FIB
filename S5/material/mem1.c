#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_ITERATIONS 	3
#define REGION_SIZE		4096

char globalArray[REGION_SIZE];

int
main (int argc, char *argv[])
{
  char buff[80];
  int niterations = DEFAULT_ITERATIONS;
  int i;
  char localArray[REGION_SIZE];
  char *p;

  if (argc > 2)
    {
      sprintf (buff, "Usage: mem1 [numMallocs]\n");
      write(2,buff,strlen(buff));
      exit (1);
    }

  if (argc == 2)
    {
      niterations = atoi (argv[1]);
    }

  sprintf (buff, "Addresses:\n");
  write(1,buff,strlen(buff));
  sprintf (buff, "\tglobalArray: %p\n", globalArray);
  write(1,buff,strlen(buff));
  sprintf (buff, "\tlocalArray: %p\n", localArray);
  write(1,buff,strlen(buff));
  sprintf (buff, "\tp: %p\n", &p);
  write(1,buff,strlen(buff));


  for (i = 0; i < niterations; i++)
    {
      p = malloc (REGION_SIZE);
      sprintf (buff, "\tp: %p, region %d: %p\n", &p, i, p);
      write(1,buff,strlen(buff));
    }

  while (1);

}
