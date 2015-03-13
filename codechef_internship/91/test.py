import random

from random import randint

t = int(raw_input())

print t

while t>0:
	t = t-1
	x = random.randint(10000,100000000)
	print("%.2f" % x)
