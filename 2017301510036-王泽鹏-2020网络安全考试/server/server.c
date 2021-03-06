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
#include <pthread.h>
#include <sys/times.h>
#include <sys/select.h>

#define MYPORT  8887
#define QUEUE   20	// socket可以排队的最大连接数

void reverse_string(char* s, int length)
{
	char tmp[length];
	for(int i=0; i<length-1; i++)	// read到buffer最后有一个换行符，这个符号不做处理
		tmp[i]=s[length-i-2];
	for(int i=0; i<length-1; i++)
		s[i]=tmp[i];
}

void data_handle(int fd)
{
	char buffer[256]; // 存储客户端信息	
	
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
	//服务端无需判断attack，通过读数据就可以直接触发缓冲区溢出漏洞		
		int size = read(fd, buffer, 276);	// read会读取输入的换行符
		//printf("size = %d",size);

		if(strcmp(buffer,"exit\n")==0)
		    break;
	
		if(size == 276)	break;

		printf("recieve message from client:");
		fputs(buffer, stdout);
		reverse_string(buffer, strlen(buffer));
		write(fd,buffer,strlen(buffer));
	}
	printf("One client disconnected successfully...\n");
	close(fd);
}

int main()
{
    printf("Begin listening...\n");
    //定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    //定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind error");
        exit(1);
    }

    //listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1)
    {
        perror("listen error");
        exit(1);
    }

    // select 超时设置
    fd_set set;
    FD_ZERO(&set);	// clear the set
    FD_SET(server_sockfd,&set);	// add our file descriptor to the set
    struct timeval tout;
    tout.tv_sec=10;	//second
    tout.tv_usec=0;	//millisecond

    //select  0:out_of_time  >0:avaliable
    if (select(server_sockfd+1, &set, NULL, NULL, &tout) == -1)
    {
	printf("select error\n");
	exit(1);
    }
    if (select(server_sockfd+1, &set, NULL, NULL, &tout) == 0)
    {
	printf("Timeout!\n");
	exit(1);
    }

    printf("Waiting for a connection...\n");
    while(1)
    {	
	//客户端套接字
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
	//成功返回非负描述字，出错返回-1
    	int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    	if(conn<0)
    	{
        	perror("connect error");
        	//exit(1);
		continue;
    	}
	
   	printf("One client connected successfully...\n");
	data_handle(conn);
    }

    close(server_sockfd);

    printf("Server shuts down\n");
    return 0;
}
