#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmpfunc(const void *a,const void *b)
{
	return *(int *)a - *(int *)b;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		int a[n];
		int i;
		for(i=0;i<n;i++)
			scanf("%d",&a[i]);
		qsort(a,n,sizeof(int),cmpfunc);
		int temp=a[0];
		for(i=1;i<n;i++)
		{
			if(temp>=a[i])
				break;
			temp = a[i];
		}
		if(i<n)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
