#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
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
		printf("%s\n",addr);
	}

	return 0;

}
