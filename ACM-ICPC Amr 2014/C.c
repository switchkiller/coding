#include<stdio.h>
#include<stdlib.h>

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m,x;
		scanf("%d %d %d",&n,&m,&x);
		int a[n];
		int i;
		for(i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			a[i]*=20;
		}
		int j,temp=0,count=0;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				temp = a[i]+a[j];
				temp /= 20;
				count+=(temp%m <=x);
			}
		}
		printf("%d\n",count);
	}
	return 0;
}
