#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int pfd[2];
    pid_t cpid;
    char buf[1024];
    int vcount = 0;
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
        ssize_t nread = read(pfd[0], buf, sizeof(buf) - 1);
        if (nread == -1) 
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buf[nread] = '\0'; 
        close(pfd[0]);
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
    } 
    else 
    {
        close(pfd[0]); 
        printf("Enter your string: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) 
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        buf[strcspn(buf, "\n")] = '\0';
        write(pfd[1], buf, strlen(buf));
        close(pfd[1]); 
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
