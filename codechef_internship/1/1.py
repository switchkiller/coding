#Write a function that computes the list of the first 100 Fibonacci numbers

f1 = 1					#intitialize f1 and f2 to 1 , the first two numbers of the Fibonacci series
f2 = 1
print "1\n1"				#print the first two numbers
for i in range(98):			
	print f1+f2			# f(n) = f(n-1) + f(n-2) , hence print f1+f2
	t = f1				
	f1 = f2				#update f1 to f(n-1)
	f2 = f1+t			#update f2 to f(n-1)+f(n-2)
