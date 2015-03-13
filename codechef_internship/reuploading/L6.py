t = int(raw_input())
while t>0:
	t = t-1
	k=int(raw_input())
	M=0
	for i in range(0,k):
	    a=int(raw_input())
	    if(i==0):
	        M=a
	    if(M<a):
	        M=a
	print M  
