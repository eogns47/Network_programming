#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char** argv) {
  int sock;
  char message[BUF_SIZE];
  int str_len;
  socklen_t adr_sz;

  struct sockaddr_in serv_adr, from_adr;

  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    error_handling("socket() error");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(9595);
  serv_adr.sin_port = htons(9595);
}
