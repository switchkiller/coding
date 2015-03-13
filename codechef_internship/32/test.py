import random
from random import randint

deck = list(range(1,16))
random.shuffle(deck)
print '15'
for i in range(len(deck)):
	print deck[i]
