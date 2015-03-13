def gcd(a,b):
    while(b!=0):
        t=b;
        b=a%b;
        a=t;
    return a;

t = int(raw_input())
while t>0:
	t = t-1
	a,b=raw_input().split(' ');
	a = int(a)
	b = int(b);
	print gcd(a,b);
