#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(){
	int client_socket=0;
	
	struct sockaddr_in server_addr;

	memset(&server_addr,0,sizeof(server_addr));
	
	client_socket=socket(PF_INET,SOCK_STREAM,0);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(4000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));

	char buff_rcv[1024];
	char buff_snd[1024];
	while(1){
		scanf("%s",buff_snd);
		write(client_socket,buff_snd,strlen(buff_snd)+1);
		if(strcmp(buff_snd,"bye")==0){
			break;		
		}
		read(client_socket,buff_rcv,1024);
		printf("%s = %s\n",buff_snd,buff_rcv);
	}
	close(client_socket);
}

