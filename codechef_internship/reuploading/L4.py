t = int(raw_input())
while t>0:
	t = t-1
	array=[]
	k=int(raw_input())
	flag=0
	for i in (0,k):
		a=int(raw_input())
		array.append(a)
	
#	for i in (1,k):
#		if(array[i]<array[i-1]):
#			flag=1

	ans = sorted(array)
	flag = (ans == array)
	if(flag==1):
	    print True
	else:
	    print False
