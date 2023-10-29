#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>


typedef struct tcp{
        char cmd;
        int len;
        char data[255];
}Tcp;

int main(){
        int client_socket =0;

        struct sockaddr_in server_addr;

        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(4000);
        server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

        client_socket=socket(PF_INET,SOCK_STREAM,0);

	if(-1==connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))){
		printf("접속실패");
	}

	Tcp tcp1;
	while(1){
		scanf("&s",tcp1.data);
		if(strcmp(tcp1.data,"q")==0){
			tcp1.len=strlen(tcp1.data);
			tcp1.cmd=0xff;
		}
		else{
			tcp1.len=strlen(tcp1.data);
			tcp1.cmd=0x0a;
		}
		write(client_socket,&tcp1,sizeof(tcp1));

	}
	close(client_socket);
	return 0;
}

	
