def triangle(a,b,c):
	if (((a+b)>c)and((b+c)>a)and((c+a)>b)):
			return True;
	else:
		return False;

a=input();
b=input();
c=input();
print triangle(a,b,c);	
