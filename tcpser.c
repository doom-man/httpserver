#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#define BUFSIZE 4096

char * vroot = "/home/dra";
struct sockaddr_in server;
struct sockaddr_in client;
int sockfd , connfd ;
char recvbuf[BUFSIZE],sendbuf[BUFSIZE];

void cleanbuf(char * buf)
{
    bzero(buf , sizeof(buf));
}

void err_quit(int num, char *string)
{
    printf("%s", string);
    exit(num);
}
int connect_establish()
{
    int len;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("create socketfd failed");
        exit(-1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
	int opt = SO_REUSEADDR;
	setsockopt(sockfd , SOL_SOCKET, SO_REUSEADDR,&opt,sizeof(opt));
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1){
        err_quit(-1, "bind error");
    }
    if (listen(sockfd, 5) == -1){
        err_quit(-1, "listen error");
    }
    len = sizeof(client);
    if((connfd = accept(sockfd , (struct sockaddr *)&client , &len))==-1){
    err_quit(-1, "accpet error");
    }
	printf("client connect successful\n");
}

int ls(char * buf,char * path){
    DIR * dir;
    cleanbuf(buf);
    int cnt=0;
    struct dirent * rent;
    dir = opendir(path);
    while((rent = readdir(dir))){
            strcpy(&buf[cnt] , rent->d_name);
            cnt+= strlen(rent->d_name);
            buf[cnt++]=' '; 
            buf[cnt] = '\0';
            if (cnt > BUFSIZE)
                   err_quit(-1,"over flow");
    }
    closedir(dir);
	return cnt;
}

void dataprocess(){
    struct stat detail;
    char * name;
begin:
    cleanbuf(recvbuf);
    cleanbuf(sendbuf);
    read(connfd , recvbuf , BUFSIZE);
    if(lstat(recvbuf,&detail)==-1){
        write(connfd , "not exit  please send agin " , BUFSIZE);
        goto begin;

    }
    if(!S_ISDIR(detail.st_mode)){
        write(connfd , "NOT a dir send agin",BUFSIZE);
        goto begin;
    }
    name = recvbuf;
    ls(sendbuf,name);
    write(connfd , sendbuf , BUFSIZE);
}

int main(int argc, char *argv[]){
    connect_establish();
    chdir(vroot);
    int num = ls(sendbuf,vroot);
	int cnt=0;
    printf("%s",sendbuf);
    fflush(stdout);
    if((cnt = write(connfd , sendbuf , num ) )< 0 )
            err_quit(-1,"\nerror with warite\n");
    printf("\n%d\n",cnt); 
    dataprocess();
    // ls(recvbuf,"fff");
    // write(connfd , recvbuf,sizeof(recvbuf));
    // system("pwd");
	close(connfd);
	close(sockfd);
    return 0;
}
 
