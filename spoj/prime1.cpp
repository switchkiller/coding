#include<bits/stdc++.h>

int flag[1000000000];

void sieve()
{
	
}

int main()
{
	int T;
	cin >> T;
	memset(flag,0,4*1000000000);
	sieve();
	while(T--)
	{
		int n,m;
		cin >> m >> n;
		for(i=m;i<=n;i++)
		{
			if(flag[i])
				cout >> i >> endl;
		}
		cout >> endl;
	}
	return 0;
}
