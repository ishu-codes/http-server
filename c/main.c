#include <netinet/in.h> // sockaddr_in
#include <stdio.h>      // perror, printf
#include <stdlib.h>     // exit, EXIT_FAILURE
#include <string.h>     // memset
#include <sys/socket.h> // socket, AF_INET, SOCK_STREAM
#include <unistd.h>     // close

#define PORT 8080
#define BUFFER_SIZE 2048 // 2KB

int main() {
  struct sockaddr_in address;
  int server_fd;

  // socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("Error while creating socket.");
    exit(EXIT_FAILURE);
  }

  // bind
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Error while binding to socket.");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  // listen
  if (listen(server_fd, 100) < 0) {
    perror("Error while listening requests.");
    close(server_fd);
    exit(EXIT_FAILURE);
  }
  printf("Listening on localhost:%d\n", PORT);

  socklen_t addr_size = sizeof(address);
  char *buffer[BUFFER_SIZE] = {};
  memset(buffer, 0, BUFFER_SIZE);
  while (1) {
    // accept
    int socket_fd = accept(server_fd, (struct sockaddr *)&address, &addr_size);
    if (socket_fd < 0) {
      perror("Error while accepting requests.");
      continue;
    }

    // recv
    if (recv(socket_fd, buffer, BUFFER_SIZE, 0) > 0) {
      printf((const char *)&buffer);

      // send
      char *response =
          "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: "
          "close\r\n\r\nHello from server!";
      send(socket_fd, response, strlen(response), 0);
    }
    close(socket_fd);
  }
  close(server_fd);

  return 0;
}
