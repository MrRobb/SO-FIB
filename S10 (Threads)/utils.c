#include <stdio.h>
#include <string.h>
#include <errno.h>                                                            
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

/* ************************************************************************ */
/*            Timing 							    */
/* ************************************************************************ */

double timer() {
	struct timeval time;
	gettimeofday(&time, 0);
	return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}

double timersec() {
	struct timeval time;
	gettimeofday(&time, 0);
	return ((double)time.tv_sec + ((double)time.tv_usec *(double)1e-6));
}
