#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char **argv) {
  int client_socket;

  struct sockaddr_in server_addr;

  char buff[BUFF_SIZE + 5];

  client_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    printf("Client socket 생성 실패\n");
    exit(1);
  }

  memset(&server_addr, 0x00, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(4001);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(client_socket, (struct sockaddr *)&server_addr,
              sizeof(server_addr)) == -1) {
    printf("connect() 실행 실패\n");
    exit(1);
  }

  char message[255];
  scanf("%s", message);

  char buf[1024];
  while (1) {
    read(client_socket, buf, 1024);
    if (strcmp(buf, "BYE") == 0) break;
    printf("receive: %s \n", buf);
  }
  close(client_socket);

  return 0;
}
