#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define e 0.577

int main()
{
	float n,ans;
	scanf("%f",&n);
	while(n!=0)
	{
		n += 1;
		n -= e;
		ans = exp(n);
		ans = ans-1;
		if(ans-(int)ans > 0.5)
			printf("%d\n",(int)ans+1);
		else
			printf("%d\n",(int)ans);
		scanf("%f",&n);
	}
}
