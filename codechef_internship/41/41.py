t = int(raw_input())
while t>0:
	t = t-1
	inp = []
	n = int(raw_input())
	inp = raw_input().split(' ')
	for i in range(n):
		inp[i] = int(inp[i])
	ans = mergesort(*inp)
	
