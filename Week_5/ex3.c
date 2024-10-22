#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		fprintf(stderr, "Fork Failed\n");
		exit(-1);
	}
	else if(pid==0)
	{
		execl ("/bin/wc", "wc", "-l", "ex1.c", (char *) 0);
    }
    else
    {
    	wait(NULL);
    	printf("Child Complete\n");
    	exit(0);
    }		
}