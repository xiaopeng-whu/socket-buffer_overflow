#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char* s, int length)
{
	char tmp[length];
	for(int i=0; i<length-1; i++)
		tmp[i]=s[length-i-2];
	//printf("%s",tmp);
	for(int i=0; i<length-1; i++)
		s[i]=tmp[i];
}

int main(void)
{
	char str[100] = "test123 abc\n";
	reverse_string(str, strlen(str));
	printf("%s",str);
	return 0;
}
