#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pidPadre ;
int a ;


void *childfunction (void)
{
	char buf[100];
	sprintf(buf, "I am the child and my father is %d. Value of a=%d (BEFORE)\n",  pidPadre, a);
	write (1, buf, strlen(buf));
	a = 1;
	sprintf(buf, "I am the child and my father is %d. Value of a=%d (AFTER)\n",  pidPadre, a);
	write (1, buf, strlen(buf));
	exit(0);
}

main()
{
	int ret;
	char buf[100];


	pidPadre = getpid();
	sprintf(buf,"Before fork (pid=%d)\n", pidPadre);
	write (1, buf, strlen(buf));

	a = 666;

	ret = fork();
	if (ret == 0) {
		childfunction();
	}
	sprintf(buf,"I am the parent (pid=%d)\n", getpid());
	write (1, buf, strlen(buf));
	waitpid(-1, NULL, 0);
	sprintf(buf,"I am the parent and a=%d\n", a);
	write (1, buf, strlen(buf));
}
