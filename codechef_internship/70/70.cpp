/*Write a function to merge two sorted arrays into a third array by preserving
 the order (i.e., all the elements in the final array are also sorted). An array
 is sorted when its elemnts are in a non-decreasing order. You cannot use any
 other array.
 
 Write a program to test the above function. Assume that both the initial 
 arrays to be merged are of the same size 5 and the resulting array is of size 10. 
 
 The two arrays to be merged should be taken as input from the user (assume 
 that the input will be in increasing order). You may also assume that all the elements
 in the two arrays are distinct.
 
 Example:
 
 If the inputs are
 
 -1 2 5 7 12
 
 and
 
 -3 0 8 9 15
 
 the output should be
 
 -3 -1 0 2 5 7 8 9 12 15*/


#include<bits/stdc++.h>
#include<iostream>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int n,m,i=0,j=0;

		cin >> n >> m;

		int a[n],b[m];				// create two arrays of size  n and m.

		for(int k=0;k<n;k++)
			cin >> a[k];

		for(int k=0;k<m;k++)
			cin >> b[k];

		int sorted[n+m];			// create the sorted array of size n+m;
		int k=0;

		while(i<n && j<m)
		{
			if(a[i]<b[j])
				sorted[k++] = a[i++];	//set the values of the sorted array accordingly
			else
				sorted[k++] = b[j++];	
		}
		while(i<n)
			sorted[k++] = a[i++];		//append the left out elements of one of the arrays

		while(j<m)
			sorted[k++] = b[j++];

		for(i=0;i<k;i++)
			cout << sorted[i] << " ";

		cout << endl;
	}
	return 0;
}
