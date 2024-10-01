#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
struct num
{
	int *a;
	int n;
	int sum;
};
void* child_thread(void *param)
{
	int sum=0;
	struct num *digits=(struct num *)param;
	for(int i=0;i<digits->n;i++)
	{
		if(digits->a[i]>=0)
			sum+=digits->a[i];
	}
	digits->sum=sum;
}
int main()
{
	struct num digits;
	printf("enter number of digits in array\n");
	scanf("%d",&digits.n);
	printf("enter numbers\n");
	digits.a= (int *)calloc(digits.n, sizeof(int));
	for(int i=0;i<digits.n;i++)
		scanf("%d",&digits.a[i]);
	pthread_t thread;
	pthread_create( &thread, 0, &child_thread, (void **)&digits);
	pthread_join( thread,(void **)&digits);
	printf("sum is %d\n",digits.sum);
}