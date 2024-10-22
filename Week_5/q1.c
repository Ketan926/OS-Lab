#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <wait.h>
int main()
{
	int status;
	char *message;
	int n;
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		printf("ERROR child not created\n");
		exit(1);
	}

	else if (pid == 0) /* child process */
	{
		printf("I'm the child!\n");
		message = "The child is executing";
		n=2;
	}
	else /* parent process */
	{
		wait(&status);
		printf("I'm the parent!\n");
		message = "The parent is executing";
		n=1;
	}
	for(; n > 0; n--) 
	{
		puts(message);
		sleep(1);
	}
}