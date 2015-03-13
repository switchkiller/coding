'''
Given the first term 'a' and common difference 'd' of an Arithmetic
progression,find the sum of the first 'n' terms of the sequence. Avoid using the formula or 
better verify the formula n*(2*a+(n-1)d)/2
'''

test = int(raw_input())
while test>0:
	a,d,n = [int(x) for x in raw_input().split(' ')]

	SUM = 0
	for i in range(n):
		SUM = SUM+a+ i*d
	print SUM
	test = test-1
