#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
	pid_t pid;
	char *message;
	int n;
	printf("fork program starting\n");
	pid = fork();
	switch(pid)
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			printf("Pid of child is %d\n",getpid());
			printf("PPid of child is %d\n",getppid());
			break;
		default:
			printf("Pid of parent is %d\n",getpid());
			printf("Pid of child in parent is %d\n",pid);
			break;
	}
	exit(0);
}