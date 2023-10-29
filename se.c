#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef struct tcp{
	char cmd;
	int len;
	char data[255];
}Tcp;

int main(){
	int server_socket =0;
	int client_socket =0;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	memset(&server_addr,0,sizeof(server_addr));
	memset(&client_addr,0,sizeof(client_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(4000);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	server_socket=socket(PF_INET,SOCK_STREAM,0);

	bind(server_socket, (struct sockaddr*)&server_addr,sizeof(server_addr));

	listen(server_socket,6);

	int client_addr_size=sizeof(client_addr);
	client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_size);

	Tcp tcp1;
	memset(&tcp1,0,sizeof(tcp1));
	if(client_socket==-1){
		printf("클라이언트연결수락실패");
		exit(0);
	}
	else printf("클라이언트 연결 성공\n");
	while(1){
		int a=read(client_socket,&tcp1,sizeof(tcp1));
		printf("%d",a);
		if(tcp1.cmd==0xff){
			break;
		}
		else if(tcp1.cmd==0x0a){
			printf("reveive data:");
			for(int i=0; i<tcp1.len; i++){
				printf("%c",tcp1.data[i]);
			}
			printf("\n");
		}
		else{
			printf("error\n");
		}
		tcp1.cmd=0x0b;
		tcp1.len=0;
		write(client_socket,&tcp1,sizeof(tcp1));

	}
	close(client_socket);
	close(server_socket);

	return 0;
}
