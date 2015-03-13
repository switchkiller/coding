t = int(raw_input())
while t>0:
	t = t-1
	k=input();
	array=[];
	for i in range(0,k):
	    a=input();
	    array.append(a);

	ans=0;
	for i in range(0,k):
	    ans+=array[i];
	print ans;
    

