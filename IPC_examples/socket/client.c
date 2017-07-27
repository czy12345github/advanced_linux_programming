#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int socket_fd;
  struct sockaddr_un name;

  if(argc != 3){
    printf("Usage : %s <socket_name> <text>\n", argv[0]);
    exit(0);
  }

  socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
  name.sun_family = AF_LOCAL;
  strcpy(name.sun_path, argv[1]);
  connect(socket_fd, &name, SUN_LEN(&name));
  write(socket_fd, argv[2], strlen(argv[2]) + 1);
  close(socket_fd);
  return 0;
}
