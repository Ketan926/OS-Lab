#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "my_fifo2"

int main()
{
    int digits[4];
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;

    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    if (pipe_fd == -1) 
    {
        perror("Open FIFO failed");
        exit(EXIT_FAILURE);
    }

    res = read(pipe_fd, digits, sizeof(digits));
    if (res == -1) 
    {
        perror("Read error on pipe");
        exit(EXIT_FAILURE);
    }

    (void)close(pipe_fd);

    printf("Process %d finished, %d bytes read\n", getpid(), res);
    printf("Received data: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", digits[i]);
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}
