def triangle(a,b,c):
	if (((a+b)>c)and((b+c)>a)and((c+a)>b)):
		if (((a==b)and(a!=c))or((b==c)and(a!=c))or((a==c)and(b!=c))):
			return True;
	else:
		return False;
	return False;

t = int(raw_input())
while t>0:
	t = t-1
	a,b,c=raw_input().split(' ');
	a = int(a)
	b = int(b)
	c = int(c)
	print triangle(a,b,c);	
