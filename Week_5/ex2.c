#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
	int status;
	pid_t pid;
	pid = fork();
	if(pid == -1)
		printf("\nERROR child not created\n");
	else if (pid == 0) /* child process */
	{
		printf("\n I'm the child!\n");
		exit(0);
	}
	else /* parent process */
	{
		printf("status is %d\n",status);
		wait(&status);
		printf("\n I'm the parent!\n");
		printf("\n Child returned: %d\n", status);
	}
}