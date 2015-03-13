def power(x,y,pro):
    if(y==0):
        return pro
    else:
        return power(x,y-1,pro*x)

t = int(raw_input())
while t>0:
	t = t-1
	a,b=raw_input().split(' ')
	a = int(a)
	b = int(b)
	print power(a,b,1)
