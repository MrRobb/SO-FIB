all: createProcesses createThreads fork_compartMem thread_compartMem threads_racecondition thread_compartMem2 fork2pthread sumavector

utils.o: utils.c 
	gcc  -c utils.c 

createProcesses: createProcesses.c utils.o
	gcc  createProcesses.c utils.o -o createProcesses

createThreads: createThreads.c utils.o
	gcc -pthread  createThreads.c utils.o -o createThreads

fork_compartMem: fork_compartMem.c
	gcc  fork_compartMem.c  -o fork_compartMem

thread_compartMem: thread_compartMem.c
	gcc -pthread  thread_compartMem.c  -o thread_compartMem

thread_compartMem2: thread_compartMem2.c
	gcc -pthread  thread_compartMem2.c  -o thread_compartMem2

threads_racecondition: threads_racecondition.c
	gcc -pthread  threads_racecondition.c  -o threads_racecondition

fork2pthread: fork2pthread.c 
	gcc  fork2pthread.c -o fork2pthread

sumavector: sumavector.c 
	gcc  sumavector.c -o sumavector

clean:
	rm -f *.o createThreads createProcesses fork_compartMem thread_compartMem thread_compartMem2 threads_racecondition sumavector fork2pthread 

