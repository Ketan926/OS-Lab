#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
int main()
{
	int fd = open("file.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		perror("open");
		return 1;
	}
	printf("file descriptor: %d\n", fd);
	close(fd);
	return 0;
}