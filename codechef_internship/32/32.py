'''
Write a recursive function to calculate the number of configuration of n
rooks on an n-by-n chessboard such that no two rooks can attack each other in the
next move (i.e., no two rooks lie on the same row or same column).
Note you just have to print the number of possible configuration and not the
configuration itself.
'''

def n_perm(x):
	if(x==1):
		return 1
	else:
		return x*n_perm(x-1)
	

test = int(raw_input())

while test>0:
	test = test-1
	n = int(raw_input())
	print n_perm(n)

'''
Solution: The answer can be obtained by getting n!. Let us do this piece by piece. The first can be placed on any squareof the diagonal.Hence this piece can be placed in n^2 ways. Similarly , the next piece can be placed in (n-1)^2 ways.
But the rooks are simillar. Hence the answer will be (n!)^2 / (n!) which brings us to n! .
'''
