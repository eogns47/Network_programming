#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	int server_socket=0;
	int client_socket=0;

	socket sockaddr_in server_addr;
	socket sockaddr_in client_addr;

	memset(&server_addr,0,sizeof(server_addr));
	memset(&client_addr,0,sizeof(client_addr));

	server_socket=socket(PF_INET,SOCK_STREAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin.port = htons(4000);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));

	listen(server_socket,5);

	char buff[1024];
	char buff_rcv[1024];
	char buff_snd[1024];

	while(1){
		int client_addr_size=0;
		client_addr_size=sizeof(client_addr);
		client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_size);
		while(1){
			read(client_socket,buff_rcv,1024);
			if(strcmp(buff_rcv,"bye")==0){
				close(client_socket);
				break;
			}
			printf("buff_rcv : %s\n",buff_rcv);

			if(strstr(buff_rcv,"+")!=NULL){
				char *a=strtok(buff_rcv,"+");
				char *b=strtok(NULL,"+");
				int result=int(a)-48+int(b)-48;
			}
			sprintf(buff_snd,"%d",result);
			write(client_socket,buff_snd,1024);
			

		}
}
