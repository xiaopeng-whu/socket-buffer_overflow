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
#define BUFFER_SIZE 1024

int main()
{
    ///定义sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //本机ip作测试
    //servaddr.sin_addr.s_addr = inet_addr("10.0.2.5");	//服务器ip

	// 扫描局域网ip，寻找目标服务器连接
	char addr[11]="10.0.2.x"; // 最后留一位作结束符
	char end_ip[4];	// 存放第四字段的ip值，最后留一位作结束符
	
	for(int i=0; i<256; i++)
	{
		memset(end_ip,'\0',sizeof(end_ip));	// 字符数组置空
		sprintf(end_ip, "%d", i);	// 实现int转换为char类型
		for(int j=0; j<strlen(end_ip); j++)
		{
			addr[j+7]=end_ip[j];
		}
		//printf("%s\n",addr);
		servaddr.sin_addr.s_addr = inet_addr(addr);
		if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0)
			printf("%s is exist. Connect successfully!\n", addr);
		else	//连接服务器成功返回0,失败返回-1
			printf("%s is not exist.\n", addr);
	}


    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    memset(sendbuf, 0, sizeof(sendbuf));
    memset(recvbuf, 0, sizeof(recvbuf));
    printf("Please input a string to reverse('exit' to quit):");
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
		write(sock_cli, sendbuf, 1024);
        if(strcmp(sendbuf,"exit\n")==0)
            break;
		read(sock_cli, recvbuf, 1024);
		//printf("recieve message from server:");
        fputs(recvbuf, stdout);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
		printf("Please input a string to reverse('exit' to quit):");
    }
	printf("Client is disconnected from server.\n");
    close(sock_cli);
    return 0;
}
