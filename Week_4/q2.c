#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LINES 20

int main(int argc, char *argv[]) 
{
    for (int i = 1; i < argc; i++) 
    {
        printf("Displaying file: %s\n", argv[i]);
        int fd = open(argv[i], O_RDONLY);
    	char buffer[1024];
    	ssize_t n;
    	int line_count = 0;

    while ((n = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        for (ssize_t i = 0; i < n; i++) 
        {
            printf("%c",buffer[i]);
            if (buffer[i] == '\n') 
            {
                line_count++;
                if (line_count >= LINES) 
                {
                	break;
                    line_count = 0;
                }
            }
        }
    }
    }

    return 0;
}
