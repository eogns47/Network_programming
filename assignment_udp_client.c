#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PacketSize 4104
#define file_name "file1.txt"
void error_handling(char* message);

typedef struct packet {
  char data[4096];  // 데이터
  int data_size;    // 데이터 사이즈
  int data_seq;     // 데이터 시컨스
} Packet;

int main(int argc, char** argv) {
  int sock;
  int str_len;
  socklen_t adr_sz;
  Packet packet;
  packet.data_seq = 0;

  FILE* file = fopen(file_name, "rb");
  if (file == NULL) {
    perror("Error opening file");
    exit(1);
  }

  struct sockaddr_in serv_adr, from_adr;

  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    error_handling("socket() error");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  while (1) {
    packet.data_size = fread(packet.data, 1, sizeof(packet.data), file);
    packet.data_seq++;

    if (packet.data_size <= 0) {
      break;
    }

    sendto(sock, (Packet*)&packet, PacketSize, 0, (struct sockaddr*)&serv_adr,
           sizeof(serv_adr));

    printf("%d byte data (seq %d) send.\n", packet.data_size, packet.data_seq);
  }
  packet.data[0] = 0x1A;
  sendto(sock, (Packet*)&packet, PacketSize, 0, (struct sockaddr*)&serv_adr,
         sizeof(serv_adr));
  close(sock);
  return 0;
}

void error_handling(char* message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}