#include <pthread.h>
#include <stdio.h>
struct num
{
	int l,u;
};
int isprime(int n)
{
	for(int i=2;i<n;i++)
	{
		if(n%i==0)
			return 0;
	}
	return 1;
}
void* child_thread(void *param)
{
	struct num *digits=(struct num *)param;
	int low=digits->l;
	int upper=digits->u;
	printf( "Starting thread\n");
	for(int i=low;i<=upper;i++)
	{
		if(isprime(i)!=0)
		{
			printf("%d ",i);
		}
	}
	printf("\n");
}
int main()
{
	struct num digits;
	printf("enter lower bound and upper bound\n");
	scanf("%d%d",&digits.l,&digits.u);
	pthread_t thread;
	pthread_create( &thread, 0, &child_thread, (void **)&digits);
	pthread_join( thread,0);
}