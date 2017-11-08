#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>

#define PENDINGCONNECTIONS 10



// Create a socket and initialize it to be able to accept 
// connections.
// It returns the virtual device associated to the socket that should be used 
// in the accept system call, to get the virtual device associated to 
// the connection
//

int
createSocket (char *socketId)
{
  int ret;
  int socket_fd;
  struct sockaddr_un socketAddr;

  socketAddr.sun_family = PF_UNIX;
  strcpy (socketAddr.sun_path, socketId);

  socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);
  if (socket_fd < 0)
    return socket_fd;

  ret =
    bind (socket_fd, (struct sockaddr *) &socketAddr, sizeof (socketAddr));
  if (ret < 0)
    {
      close (socket_fd);
      return ret;
    }

  ret = listen (socket_fd, PENDINGCONNECTIONS);
  if (ret < 0)
    {
      close (socket_fd);
      return ret;
    }

  return socket_fd;
}


// Returns the file descriptor associated to the connection.
// accept system call will fill the socketAddr parameter
// with the address of the socket for the client which is requesting the
// connection, and the addrSize parameter with the size of that address.

int
serverConnection (int socket_fd)
{
  struct sockaddr_un sockAddr;
  socklen_t addrSize;

  return (accept (socket_fd, (struct sockaddr *) &sockAddr, &addrSize));

}

// Returns the socket virtual device that the client should use to access 
// the socket, if the connection is successfully established 
// and -1 in case of error
//
// Connect system call requires the address of the 
// server socket to request the connection and the size of that address.
//

int
clientConnection (char *socketId)
{

  struct sockaddr_un sockAddr;
  int socket_fd;
  int ret;

  //creates the virtual device for accessing the socket
  socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);
  if (socket_fd < 0)
    return socket_fd;

  sockAddr.sun_family = PF_UNIX;
  strcpy (sockAddr.sun_path, socketId);

  ret = connect (socket_fd, (struct sockaddr *) &sockAddr, sizeof (sockAddr));
  if (ret < 0)
    {
      close (socket_fd);
      return (ret);
    }

  return socket_fd;

}


int
deleteSocket (int socket_fd, char *socketId)
{
  close (socket_fd);
  unlink (socketId);
}

int
closeConnection (int connection_fd)
{
  close (connection_fd);
}
