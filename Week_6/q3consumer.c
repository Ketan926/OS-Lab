#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#define FIFO_NAME "my_fifo2"

int main()
{
    int digits[4];
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    char buf[1024]; // Buffer to read data from the pipe
    int vcount = 0;
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    if (pipe_fd == -1) 
    {
        perror("Open FIFO failed");
        exit(EXIT_FAILURE);
    }

    ssize_t nread = read(pipe_fd, buf, sizeof(buf) - 1);
    if (nread == -1) 
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    
    buf[nread] = '\0'; // Null-terminate the buffer
    close(pipe_fd);
    printf("Received string: %s\n", buf);
    for (int i = 0; i < nread; i++) 
    {
        if (tolower(buf[i]) == 'a' || tolower(buf[i]) == 'e' || tolower(buf[i]) == 'i' || tolower(buf[i]) == 'o' || tolower(buf[i]) == 'u') 
        {
            vcount++;
            printf("Vowel is %c\n", buf[i]);
        }
    }
    printf("Number of vowels is %d\n", vcount);
    exit(EXIT_SUCCESS);
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
