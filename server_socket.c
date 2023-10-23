#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char **argv) {
  int server_socket = 0;
  int client_socket = 0;
  int client_addr_size = 0;

  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  char buff[BUFF_SIZE + 5];
  char buff_rcv[BUFF_SIZE];
  char buff_snd[BUFF_SIZE];

  memset(&server_addr, 0x00, sizeof(server_addr));
  memset(&client_addr, 0x00, sizeof(client_addr));

  server_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    printf("Server socket 생성 실패\n");
    exit(1);
  }

  memset(&server_addr, 0x00, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(4000);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) == -1) {
    printf("bind() 실행 에러\n");
    exit(1);
  }

  if (listen(server_socket, 5) == -1) {
    printf("listen() 실행 실패\n");
    exit(1);
  }

  while (1) {
    client_addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                           &client_addr_size);
    if (client_socket == -1) {
      printf("클라이언트 연결 수락 실패\n");
      exit(1);
    } else {
      printf("클라이언트 연결 수락 성공\n");
    }

    read(client_socket, buff_rcv, BUFF_SIZE);
    printf("receive: %s\n", buff_rcv);

    sprintf(buff_snd, "%d : %s", strlen(buff_rcv), buff_rcv);
    write(client_socket, buff_snd, strlen(buff_snd) + 1);
    close(client_socket);
  }

  return 0;
}