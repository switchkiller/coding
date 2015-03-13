#include<iostream>
using namespace std;
float c(float n,float k)
{
	if(k==0)
	{
		return 1;
	}
	else	
		return (n/k)*c(n-1,k-1);
}
int main()
{
	float n,k;
	int test;
	cin>>test;
	while(test)
	{
		cin>>n>>k;
		cout<<c(n,k)<<endl;
		test--;
	}
	return 0;
} 
