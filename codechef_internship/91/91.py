'''
Write a function to compute the square root of an integer
'''


t = int(raw_input()) 			# Number of testcases
while t>0:
	t = t-1
	a = float(raw_input())
	print("%.2f" % a**0.5)			# sqrt(a) = a**0.5
