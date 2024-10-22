#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
	pid_t pid;
	pid = fork();
	if (pid == -1) 
	{  
    	perror("Falied to fork");
	} 
	else if(pid == 0) 
	{  	
    	printf("the childs pid is %d\n",getpid());
    	execlp ("./ex1","ex1",NULL);
	} 
	else 
	{
		wait(NULL);
    	printf("Parent Process is running\n");
	}
	exit(0);
}

