#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
 void main(void){
		 struct sockaddr_in server;
		 int sockfd;
		 char buf[1000];
		 if((sockfd = socket(AF_INET , SOCK_STREAM , 0))==-1){
				 printf("creat sockfd error");
				 exit(-1);
		 }
		 bzero(&server , sizeof(server));
		 server.sin_family = AF_INET;
		 server.sin_port = htons(8080);
		 server.sin_addr.s_addr = inet_addr("127.0.0.1");
		 if(connect(sockfd , (struct sockaddr * )&server ,sizeof(server))==-1){
				 printf("connect error");
				 exit(-1);
		 }
		 printf("Connect sucess");
		 printf("\n");
		 int cnt=0;
		 char name[20];
		 cnt=recv(sockfd , buf , 1000 ,0);
		 printf("%s",buf);
		 fflush(stdout);
		 // tcpser loop
		bzero(buf , sizeof(buf));
		scanf("%s",name);
		write(sockfd , name ,20);
		if((cnt = read(sockfd , buf , 1000))>0 ){
			printf("%s",buf);   
		} 
		
		 close(sockfd);



 }
