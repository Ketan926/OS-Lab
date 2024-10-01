#include <pthread.h>
#include <stdio.h>
void* thread_code( void * param )
{
	printf( "In thread code\n" );
	pthread_exit(0);
}
int main()
{
	pthread_t thread;
	pthread_create(&thread,NULL, &thread_code,NULL);
	printf("In main thread\n" );
	pthread_join(thread, NULL);
}