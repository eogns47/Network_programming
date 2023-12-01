#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int server_sockfd, client_sockfd;
  int client_len, n;
  int state;
  char buf[80];
  struct sockaddr_in clientaddr, serveraddr;

  // select time out 설저을 위한 timeval 구조체
  struct timeval tv;
  fd_set readfds;

  client_len = sizeof(clientaddr);
  if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket error : ");
    exit(0);
  }
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(atoi(argv[1]));

  bind(server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  listen(server_sockfd, 5);

  while (1) {
    memset(buf, 0x00, 80);
    client_sockfd =
        accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);
    // client_sockfd 의 입력검사를 위해서
    // fd_set 에 등록한다.
    FD_ZERO(&readfds);
    FD_SET(client_sockfd, &readfds);
    // 약 5초간 기다린다.
    tv.tv_sec = 5;
    tv.tv_usec = 10;

    // 입력이 있는지 기다린다.
    state = select(client_sockfd + 1, &readfds, (fd_set *)0, (fd_set *)0, &tv);
    switch (state) {
      case -1:
        perror("select error :");
        exit(0);
      // 만약 5초안에 아무런 입력이 없었다면
      // Time out 발생상황이다.
      case 0:
        printf("Time out error\n");
        break;
      // 5초안에 입력이 들어왔을경우 처리한다.
      default:
        if ((n = read(client_sockfd, buf, 80)) <= 0) {
          perror("read error : ");
          usleep(10);
          break;
        } else {
          printf("read : %s\n", buf);
        }
        if (write(client_sockfd, buf, 80) <= 0) {
          perror("write error : ");
          break;
        }
        break;
    }
    close(client_sockfd);
  }
}
