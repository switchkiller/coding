def gcd(a,b):
    if(b==0):
        return a
    else:
        t=b
        b=a%b
        a=t
    return gcd(a,b)

t = int(raw_input())

while t>0:
	t = t-1
	a,b=raw_input().split(' ')
	a = int(a)
	b = int(b)
	print gcd(a,b)
