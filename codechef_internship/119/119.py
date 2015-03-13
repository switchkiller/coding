'''
Write a function to find the Stirling number S(n,k)
'''

stir = []

def stirling(n,k):
	if n==0 or k<0 or k>n:
		return 0
	if k==n or k==1:
		return 1
	return stirling(n-1,k-1) + k*stirling(n-1,k)

test = int(raw_input())
while test>0:
	n,k = raw_input().split()
	print stirling(int(n),int(k))
	test = test-1
