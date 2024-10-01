#include <pthread.h>
#include <stdio.h>
void* child_thread( void * param )
{
	int n = (int)param;
	int sum=0;
	printf( "Starting thread\n");
	for(int i=1;i<=n;i++)
		sum+=i;
	return (void *)sum;
}
int main()
{
	pthread_t thread;
	int return_value;
	int i;
	printf("enter n value\n");
	scanf("%d",&i);
	pthread_create( &thread, 0, &child_thread, (void*)i );
	pthread_join( thread, (void**)&return_value );
	printf( "Summation upto n is %d\n", return_value);
}