import random
from random import randint


t = int(raw_input())
print t
while t>0:
	t = t-1
	n = randint(0,101)
	m = randint(0,101)
	arr1 = random.sample(range(1000000),n)
	arr2 = random.sample(range(1000000),m)
	arr1 = sorted(arr1)
	arr2 = sorted(arr2)
	print n,m
	for i in range(len(arr1)):
		print arr1[i],
	print '\n'
	for i in range(len(arr2)):
		print arr2[i],
	print '\n'
#for i in range(n):
#		print arr1[i],
#	print '\n'
#	for i in range(m):
#		print arr2[i],
#	print '\n'
