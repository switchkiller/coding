'''
Input three strings s, t and w from the user. Assume that the strings do not
contain blank or any whitespace character.
Write a function that finds all occurrence of substring t in s, and replaces
them by w. The function returns the number of such occurences or 
replacements.
Assume that t and w are of the same size.
For example,if the string s is "abcdefghidefjkl",
t is "def"
and w is "xyz",
then after replacement,
s becomes "abcxyzghixyzjkl"
and the function returns 2.
'''

test = int(raw_input())
while test>0:
	test = test-1
	s,t,w = raw_input().split(' ')
	i=-1
	count=0
	while(1):
		i = s.find(t,i+1)
		if(i==-1):
			break
		else:
			count = count+1
	print s.replace(t,w)
	print count
