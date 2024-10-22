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
			printf("This is child process\n");
			printf("Pid of child is %d\n",getpid());
			printf("PPid of child is %d\n",getppid());
			exit(0);
			break;
		default:
			printf("This is parent process\n");
			printf("Pid of parent process is %d\n",getpid());
			printf("Pid of child in parent is %d\n",pid);
			sleep(15);
			printf("parent is exiting\n");
			exit(0);
			break;
	}
	return 0;
}