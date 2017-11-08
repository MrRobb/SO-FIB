#include <stdlib.h>
#include <string.h>
#include "socketMng.c"

#define MAXSTRING 256

void error_y_exit(char*msg,int error_status) {
	perror(msg);
	exit(error_status);
}

main (int argc, char *argv[]) {
	int connectionFD;
	int ret;
	char buffer[MAXSTRING];
	char c[1];

	if (argc != 2) error_y_exit("Usage: prClientSocket socketPath\n",1);

	connectionFD = clientConnection (argv[1]);
	if (connectionFD < 0) error_y_exit("Error establishing connection\n",1);

	ret = read (connectionFD, buffer, sizeof (buffer));
	if (ret < 0) error_y_exit("Error reading from connection\n",1);

	ret = write (1, buffer, ret);

	if (ret < 0) error_y_exit("Error writing on standard output \n",1);

	strcpy (buffer, "Hello there!\n");
	ret = write (connectionFD, buffer, strlen (buffer));
	if (ret < 0) error_y_exit("Error writing on connection\n",1);

	while(read(0,c,1)>0) write(connectionFD,c,1);

	closeConnection (connectionFD);
}
