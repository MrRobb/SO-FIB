void Usage() {
	char buff[128];
	sprintf(buff, "Usage: [escribir formato de entrada]\n");
	write(1, buff, strlen(buff));
	exit (1);
}

void error_y_exit(char *msg)
{
	perror(msg);
	exit(1);
}