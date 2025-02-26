import math
import random
import numpy as np
import matplotlib.pyplot as plt

def entropy(input):
    sum = 0
    for i in range(0, len(input)):
        sum += input[i] * math.log(1 / input[i]) 
    return sum

def KL_distance(input1, input2):
    sum = 0
    for i in range(0, len(input1)):
        sum += input1[i] * math.log(input1[i] / input2[i])
    return sum

# set the number of elements of distibution
distributionDim = 5

# initialize each distributions
p1 = []
p2 = []
q1 = []
q2 = []
for i in range(0, distributionDim - 1):
    p1.append((1 - sum(p1)) * random.random())
    p2.append((1 - sum(p2)) * random.random())
    q1.append((1 - sum(q1)) * random.random())
    q2.append((1 - sum(q2)) * random.random())

p1.append(1 - sum(p1))
p2.append(1 - sum(p2))
q1.append(1 - sum(q1))
q2.append(1 - sum(q2))

# display each distributions
print(p1)
print(p2)
print(q1)
print(q2)

# main calculation
num_interval = 30
figure, ax = plt.subplots(1, 2, figsize=(10, 5))

KLD_lambda = []
KLD_first = []
KLD_second = []
for i in range(0, num_interval + 1):
    """
    Check if D(p || q) is convex in the pair (p, q)
    """
    lam = 1 / num_interval * i
    KLD_lambda.append(lam)
    KLD_first.append(KL_distance(lam * np.array(p1) + (1 - lam) * np.array(p2), lam * np.array(q1) + (1 - lam) * np.array(q2)))
    KLD_second.append(lam * KL_distance(np.array(p1), np.array(q1)) + (1 - lam) * KL_distance(np.array(p2), np.array(q2)))

ax[0].plot(KLD_lambda, KLD_first)
ax[0].plot(KLD_lambda, KLD_second)
ax[0].set_title('D(p || q) us convex in the pair (p, q)')
ax[0].legend(['One function', 'Two functions'])

entropy_lambda = []
entropy_first = []
entropy_second = []
for i in range(0, num_interval + 1):
    """
    Check if H(p) is concave in p
    """
    lam = 1 / num_interval * i
    entropy_lambda.append(lam)
    entropy_first.append(entropy(lam * np.array(p1) + (1 - lam) * np.array(p2)))
    entropy_second.append(lam * entropy(np.array(p1)) + (1 - lam) * entropy(np.array(p2)))
    """
    print(f"lambda: {lam}")
    print(entropy(lam * np.array(p1) + (1 - lam) * np.array(p2)))
    print(lam * entropy(np.array(p1)) + (1 - lam) * entropy(np.array(p2)))
    """
ax[1].plot(entropy_lambda, entropy_first)
ax[1].plot(entropy_lambda, entropy_second)
ax[1].set_title('H(p) is concave in p')
ax[1].legend(['One function', 'Two functions'])

plt.show()



