#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc , char** argv){
	int server_socket=0;
	int client_socket=0;
	int client_addr_size=0;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char buff[BUFF_SIZE+5];

	memset(&server_addr,0x00,sizeof(server_addr));
	memset(&client_addr,0x00,sizeof(client_addr));

	server_socket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(4000);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(server_socket, (struct sockaddr *)&server_addr,sizeof(server_addr));

	listen(server_socket,5);

	client_addr_size = sizeof(client_addr);
	client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);


