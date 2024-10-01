#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
struct num
{
	int *a;
	int n;
	int even_sum, odd_sum;
};
void* child_thread0(void *param)
{
	struct num *digits=(struct num *)param;
	digits->even_sum=0;
	printf( "Starting thread 0\n");
	for(int i=0;i<digits->n;i++)
	{
		if(digits->a[i]%2==0)
			digits->even_sum+=digits->a[i];
	}
}
void* child_thread1(void *param)
{
	struct num *digits=(struct num *)param;
	digits->odd_sum=0;
	printf( "Starting thread 1\n");
	for(int i=0;i<digits->n;i++)
	{
		if(digits->a[i]%2==1)
			digits->odd_sum+=digits->a[i];
	}
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
	pthread_t thread[2];
	pthread_create( &thread[0], 0, &child_thread0, (void **)&digits);
	pthread_create( &thread[1], 0, &child_thread1, (void **)&digits);
	pthread_join( thread[0],(void **)&digits);
	pthread_join( thread[1],(void **)&digits);
	printf("even sum is %d\n",digits.even_sum);
	printf("odd sum is %d\n",digits.odd_sum);
}