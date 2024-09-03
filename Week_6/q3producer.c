#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "my_fifo2"

int main()
{
    int digits[4] = {1, 2, 3, 4};  // Correct number of integers
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    char buf[1024]; // Buffer to read data from the pipe
    int vcount = 0;
    printf("Enter your string: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) 
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }
    buf[strcspn(buf, "\n")] = '\0';
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

    res = write(pipe_fd,&buf, sizeof(digits));
    if (res == -1) 
    {
        perror("Write error on pipe");
        exit(EXIT_FAILURE);
    }

    (void)close(pipe_fd);
    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}
