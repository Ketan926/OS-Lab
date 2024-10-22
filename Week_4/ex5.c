#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
int main()
{
	char *c= (char *)calloc(100, sizeof(char));
	int fp= creat("file3.txt", O_CREAT | O_RDWR | S_IRUSR | S_IWUSR | S_IXUSR);
	if (fp < 0) 
	{ 
    	perror("r1"); 
    	exit(1); 
	} 
	printf("file descriptor id: %d\n",fp);
	int sz;
	sz= write(fp, "Hello, welcome to Manipal\n", strlen("Hello, welcome to Manipal\n"));
	close(fp);
}