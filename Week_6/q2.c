#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int pfd[2];
	pid_t cpid;
	int digits[5]={1,2,3,4,5};
	int buf[5];
	int read_digits[5];
	int sum=0;
	if (pipe(pfd) == -1) 
	{
		perror("pipe");
		exit(EXIT_FAILURE); 
	}
	cpid = fork();
	if (cpid == -1) 
	{
		perror("fork");
		exit(EXIT_FAILURE); 
	}
	if (cpid == 0) 
	{ 
		close(pfd[1]);
		while (read(pfd[0], read_digits, sizeof(read_digits)) > 0)
			//write(read_digits, buf, 1);
		for(int i=0;i<sizeof(read_digits)/sizeof(int);i++)
			sum+=read_digits[i];
		printf("sum of digits %d\n",sum);
		close(pfd[0]);
		exit(EXIT_SUCCESS);
	} 
	else 
	{
		close(pfd[0]);
		write(pfd[1], digits, sizeof(digits));
		close(pfd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}