all: exServerSocket exClientSocket sin_nombre escritor escritor_socket lector lector_socket

exServerSocket: exServerSocket.c socketMng.o
	gcc -o exServerSocket exServerSocket.c socketMng.o

exClientSocket: exClientSocket.c socketMng.o
	gcc -o exClientSocket exClientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c socketMng.c

sin_nombre: sin_nombre.c
	gcc -o sin_nombre sin_nombre.c

escritor: escritor.c
	gcc -o escritor escritor.c

escritor_socket: escritor_socket.c
	gcc -o escritor_socket escritor_socket.c

lector: lector.c
	gcc -o lector lector.c

lector_socket: lector_socket.c
	gcc -o lector_socket lector_socket.c

clean: 
	rm -f exServerSocket exClientSocket *.o
