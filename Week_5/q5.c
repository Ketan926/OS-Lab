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
		printf("This is Child process\n");
		printf("The ppid of the child is %d\n",getppid());
		sleep(10);
    	printf("The childs pid is %d\n",getpid());
    	printf("The ppid of the child is %d\n",getppid());
	} 
	else 
	{
    	printf("Parent Process is running\n");
    	printf("The parents pid is %d\n",getpid());
    	printf("This has child %d\n",pid);
	}
	exit(0);
}

