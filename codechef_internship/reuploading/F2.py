t = int(raw_input())
while t>0:
	t = t-1
	a,b=raw_input().split(' ');
	a = int(a)
	b=int(b);
	add=0;
	for i in range(a,b+1):
	        add=add+i;
	print add;
