#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<stdio.h>
int main()
{
	char *c= (char *)calloc(100, sizeof(char));
	int fp= open("file3.txt", O_RDWR);
	printf("file descriptor id: %d\n",fp);

	int sz=read(fp, c, 100);
	c[sz]='\0';
	printf("those bytes are as follows: %s\n",c);
	return 0;
}