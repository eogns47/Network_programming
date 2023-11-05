#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PacketSize 4105
void error_handling(char* message);

typedef struct packet {
  char data[4096];  // 데이터
  int data_size;    // 데이터 사이즈
  int data_seq;     // 데이터 시컨스
  char code;
} Packet;

int main() {
  int server_sock;
  int str_len;
  socklen_t clnt_adr_sz;
  Packet packet;

  struct sockaddr_in server_adr, clnt_adr;

  server_sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (server_sock == -1) {
    error_handling("socket() error");
  }

  memset(&server_adr, 0, sizeof(server_adr));

  server_adr.sin_family = AF_INET;
  server_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_adr.sin_port = htons(9595);

  if (bind(server_sock, (struct sockaddr*)&server_adr, sizeof(server_adr)) ==
      -1) {
    error_handling("bind() error");
  }

  while (1) {
    clnt_adr_sz = sizeof(clnt_adr);
    str_len = recvfrom(server_sock, (Packet*)&packet, PacketSize, 0,
                       (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

    if (packet.code == 0x1A) {
      break;
    }

    if (packet.data_size <= 0) {
      break;
    }

    printf("%d byte data(seq %d) received.\n", packet.data_size,
           packet.data_seq);
  }

  close(server_sock);
  return 0;
}

void error_handling(char* message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
