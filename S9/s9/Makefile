all: exServerSocket exClientSocket crea_fichero insertarx

exServerSocket: exServerSocket.c socketMng.o
	gcc -o exServerSocket exServerSocket.c socketMng.o

exClientSocket: exClientSocket.c socketMng.o
	gcc -o exClientSocket exClientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c socketMng.c

crea_fichero: crea_fichero.c
	gcc -o crea_fichero crea_fichero.c

insertarx: insertarx.c
	gcc -o insertarx insertarx.c

clean: 
	rm -f exServerSocket exClientSocket *.o
