#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_COUNT 5
#define FIFO_NAME "my_fifo2"

int main()
{
    int count=0;
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;

    if (access(FIFO_NAME, F_OK) == -1) 
    {
        res = mkfifo(FIFO_NAME, 0666);
        if (res != 0) 
        {
            perror("Could not create fifo");
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    if (pipe_fd == -1) 
    {
        perror("Open FIFO failed");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        if(count<MAX_COUNT)
            count++;
        else
            printf("overflow, shelf count is %d\n",count);
        printf("producer shelf count is %d\n",count);
        res = write(pipe_fd,&count, sizeof(count));
        if (res == -1) 
        {
            perror("Write error on pipe");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }
    printf("Process %d finished\n", getpid());
    (void)close(pipe_fd);
    exit(EXIT_SUCCESS);
}
