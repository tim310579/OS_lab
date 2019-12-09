import random

#num = random.randint(1,4)
num = 1
print(num)
#length = random.randint(4, pow(10, 8))
length = pow(10, 8)
print(length)
for i in range(0, length):
    print(random.randint(0, 9), end = '')
