from itertools import product

def perm_wr(seq,n):
	x = (seq,)*n
	return [i for i in product(*x)]

def gen_perm_wr(seq,n):
	x = (seq,)*n
	return product(*x)

a = gen_perm_wr(['A','O','L'],5)
b = perm_wr(['A','O','L'],5)
print b
