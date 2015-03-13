'''
The following iterative sequence is defined for the set of positive integers:
	n = n/2 (n is even)
	n = 3n + 1 (n is odd)
Using the rule above and starting with 13, we generate the following sequence:
	13 > 40 > 20 > 10 > 5 > 16 > 8 > 4 > 2 > 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved
yet (Collatz Problem), it is thought that all starting numbers finish at 1.
Which starting number, under one million, produces the longest chain?
'''
col = {1:1}				# save the values already visited in col. The base case is n=1 for ans=1.

def collatz(x):
	if x in col:
		return col[x]
	if(x%2 == 0):
		T = 1+collatz(int(x/2))
	else:
		T = 1+collatz(int(3*x + 1))
	col[x]  = T
	return T

test = int(raw_input())
while test>0:
	n = int(raw_input())
	time = 0
	value = 0
	for i in range(1,n):
		t = collatz(i)
		if(time < t):
			time = t
			value = i
	print value
	test = test-1
