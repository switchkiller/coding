import random,string
from random import randint

print '100'

for i in range(99):
	n = random.randint(1,1000)
	print ''.join(random.choice(string.ascii_lowercase + string.ascii_uppercase) for _ in range(n))
