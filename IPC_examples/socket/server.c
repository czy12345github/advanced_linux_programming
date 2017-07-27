#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int server (int client_socket)
{
  while(1){
    char text[2048];

    if(read(client_socket, text, 2048) == 0)
      return 0;
    printf("%s\n", text);
    if(!strncmp(text, "quit", 4))
      return 1;
  }
}

int main(int argc, char* argv[])
{
  int socket_fd;
  struct sockaddr_un name;
  int client_sent_quit_message;

  if(argc != 2){
    printf("Usage: %s <socket_name>\n", argv[0]);
    exit(0);
  }
  socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
  name.sun_family = AF_LOCAL;
  strcpy(name.sun_path, argv[1]);
  bind(socket_fd, &name, SUN_LEN(&name));
  listen(socket_fd, 5);

  do{
    struct sockaddr_un client_name;
    socklen_t client_name_len;
    int client_socket_fd;

    client_socket_fd = accept(socket_fd, &client_name, &client_name_len);
    client_sent_quit_message = server(client_socket_fd);
    close(client_socket_fd);
  }while(!client_sent_quit_message);

  close(socket_fd);
  unlink(argv[1]);

  return 0;
}
