#include <stdlib.h>
#include <string.h>


#define MAXSTRING	256

main (int argc, char *argv[])
{
  int socketFD;
  int connectionFD;
  char buffer[MAXSTRING];
  int ret;

  if (argc != 2)
    {
      strcpy (buffer, "Usage: prServerSocket socketPath\n");
      write (2, buffer, strlen (buffer));
      exit (1);
    }

  socketFD = createSocket (argv[1]);
  if (socketFD < 0)
    {
      perror ("Error creating socket\n");
      exit (1);
    }

  connectionFD = serverConnection (socketFD);
  if (connectionFD < 0)
    {
      perror ("Error establishing connection \n");
      exit (1);
    }

  strcpy (buffer, "Hello!\n");
  ret = write (connectionFD, buffer, strlen (buffer));
  if (ret < 0)
    {
      perror ("Error writing on connection \n");
      exit (1);
    }

  ret = read (connectionFD, buffer, sizeof (buffer));
  if (ret < 0)
    {
      perror ("Error reading from connection \n");
      exit (1);
    }

  ret = write (1, buffer, ret);
  if (ret < 0)
    {
      perror ("Error writing on standard output \n");
      exit (1);
    }

  closeConnection (connectionFD);
  deleteSocket (socketFD, argv[1]);
}
