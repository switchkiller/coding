/*
A composite is a number containing at least two prime factors. For example, 15 =
3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3.
There are ten composites below thirty containing precisely two, not necessarily
distinct, prime factors: 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.
How many composite integers, n < 108, have precisely two, not necessarily distinct,
prime factors?
*/

#include<bits/stdc++.h>

using namespace std;
#define MAX 10000


int primes[MAX];

int count(int x,int y)
{
	int C = 0;
	while(x%y == 0)
	{
		C++;
		x /= y;
	}
	return C;
}


void sieve()
{
	int i,j;
	for(i=2;i<=MAX;i++)
	{
		if(primes[i]==0)
		{
			for(j=2;j*i<=MAX;j++)
				primes[i*j] += count(j*i,i);
		}
	}
}

int main()
{
	int n;
	memset(primes,0,sizeof(primes));
	sieve();
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n;
		int count =0;
		for(int i=0;i<=n;i++)
			count += (primes[i]==2);
		cout << count << endl;
	}
	return 0;
}
