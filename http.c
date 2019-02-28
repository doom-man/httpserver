#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

char root = "/home/dra";
void err_quit(int num, char *string)
{
    printf("%s", string);
    exit(num);
}
int connect_establish(int argc, char *argv[])
{
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sockfd, connfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("create socketfd failed");
        exit(-1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1){
        err_quit(-1, "bind error");
    }
    if (listen(listenfd, 5) == -1){
        err_quit(-1, "listen error");
    }
    len = sizeof(client);
    if((connfd = accept(sockfd , (struct sockaddr *)&client , &len))==-1){
    err_quit(-1 ， "accpet error");
    }

}
int main(int argc, char *argv[]){
    connect_establish(int argc , char * argv[]);
    chdir(string);
    system("pwd");
    return 0;
}
