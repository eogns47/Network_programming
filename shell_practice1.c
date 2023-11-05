#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t childPid;
  int status;

  int server_sock, client_sock;

  struct sockaddr_in server_addr, client_addr;

  server_sock = socket(PF_INET, SOCK_STREAM, 0);

  memset(&server_addr, 0, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(4000);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

  listen(server_sock, 5);
  char buff_rcv[1024];
  char buff_snd[1024];

  while (1) {
    int client_addr_size = sizeof(client_addr);
    client_sock =
        accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_size);

    childPid = fork();

    if (childPid == 0) {
      while (1) {
        read(client_sock, buff_rcv, 1024);
        if (strcmp(buff_rcv, "bye") == 0) {
          close(client_sock);
          break;
        }
        printf("buff_rcv : %s\n", buff_rcv);
        int result = 0;
        if (strstr(buff_rcv, "+") != NULL) {
          char *a = strtok(buff_rcv, "+");
          char *b = strtok(NULL, "");
          result = atoi(a) + atoi(b);
        }
        sprintf(buff_snd, "%d", result);
        write(client_sock, buff_snd, strlen(buff_snd) + 1);
      }
    }
  }
  close(server_sock);
}