#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>

void* child_thread(void *param)
{
	int n= *(int *)param;
	int l=0, r=1, t=0;
	int *arr= (int *)calloc(n, sizeof(int));
	printf("Starting thread\n");
	for(int i=0;i<n;i++)
	{
		arr[i]=l;
		t=l+r;
		l=r;
		r=t;
	}
	return arr;
}
int main()
{
	int n;
	printf("enter number of digits in array\n");
	scanf("%d",&n);
	int *a= (int *)calloc(n, sizeof(int));
	pthread_t thread;
	pthread_create( &thread, 0, &child_thread, (void *)&n);
	pthread_join( thread,(void **)&a);
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}