#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MYPORT  8887
#define QUEUE   20	// socket可以排队的最大连接数
#define BUFFER_SIZE 1024

void reverse_string(char* s, int length)
{
	char tmp[length];
	for(int i=0; i<length-1; i++)	// read到buffer最后有一个换行符，这个符号不做处理
		tmp[i]=s[length-i-2];
	for(int i=0; i<length-1; i++)
		s[i]=tmp[i];
}

int main()
{
    printf("listening...\n");
    ///定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }

    ///listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
	
    ///客户端套接字
    char buffer[BUFFER_SIZE]; // 存储客户端信息
    char buffer1[BUFFER_SIZE]; // 存储提示信息与处理信息的拼接字符串

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    ///成功返回非负描述字，出错返回-1
    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        exit(1);
    }

    printf("One clinet connected successfully...\n");

    char response[100] = "Recieved message successfully, and the reversed string is:";

    while(1)
    {
        memset(buffer,0,sizeof(buffer));
		memset(buffer1,0,sizeof(buffer1));

		read(conn, buffer, 1024);	// read会读取输入的换行符
        if(strcmp(buffer,"exit\n")==0)
            break;

		printf("recieve message from client:");
        fputs(buffer, stdout);
		reverse_string(buffer, strlen(buffer));
		strcat(buffer1,response);
		strcat(buffer1,buffer);
// 两次write导致缓冲区有问题，直接用一个buffer1存储提示信息和返回信息来一起返回
		write(conn,buffer1,strlen(buffer1));
    }
    close(conn);
    printf("One clinet disconnected successfully...\n");

    close(server_sockfd);
    return 0;
}
