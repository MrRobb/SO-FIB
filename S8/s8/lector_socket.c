#include <stdlib.h>
#include <string.h>
#include "socketMng.c"

#define MAXSTRING 256

void error_y_exit(char* msg,int error_status) {
	perror(msg);
	exit(error_status);
}

int main (int argc, char *argv[]){
	int socketFD;
	int connectionFD;
	char buffer[MAXSTRING];
	int ret;
	char c[1];

	if (argc != 2) error_y_exit("Usage: prServerSocket socketPath\n",1);

	socketFD = createSocket (argv[1]);
	if (socketFD < 0) error_y_exit("Error creating socket\n",1);

	connectionFD = serverConnection (socketFD);
	if (connectionFD < 0) error_y_exit("Error establishing connection \n",1);

	strcpy (buffer, "Hello!\n");
	ret = write (connectionFD, buffer, strlen (buffer));
	if (ret < 0) error_y_exit("Error writing on connection \n",1);

	while(read(connectionFD,c,1) > 0) write(1,c,1);

	closeConnection (connectionFD);
	deleteSocket (socketFD, argv[1]);
}
