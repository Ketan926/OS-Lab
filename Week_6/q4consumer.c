#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MIN_COUNT 0
#define FIFO_NAME "my_fifo2"

int main()
{
    int pipe_fd;
    int count;
    int res;
    int open_mode = O_RDONLY;

    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    if (pipe_fd == -1) 
    {
        perror("Open FIFO failed");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        res = read(pipe_fd,&count, sizeof(count));
        if (res == -1) 
        {
            perror("Read error on pipe");
            exit(EXIT_FAILURE);
        }
        if(count>MIN_COUNT)
        {
            count--;
            printf("Consumer removed item, shelf count is %d\n",count);
        }
        else
        {
            printf("No item to remove, shelf count is %d\n",count);
        }
        sleep(1);
    }
    printf("Process %d finished, %d bytes read\n", getpid(), res);
    (void)close(pipe_fd);
    exit(EXIT_SUCCESS);
}
