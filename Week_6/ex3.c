#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *filename, mode_t mode);
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
	int res = mkfifo("my_fifo2", 0777);
	if (res == 0) printf("FIFO created\n");
	exit(EXIT_SUCCESS);
}