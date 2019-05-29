import numpy as np
import matplotlib.pyplot as plt

dataNum = 1000

X = np.zeros((dataNum*4, 2))

X[0:dataNum, :] = np.random.randn(dataNum, 2)
X[dataNum:dataNum*2, :] = np.random.randn(dataNum, 2)
X[dataNum*2:dataNum*3, :] = np.random.randn(dataNum, 2)
X[dataNum*3:dataNum*4, :] = np.random.randn(dataNum, 2)

X[dataNum:dataNum*2, 0] = np.random.randn(dataNum) + 8
X[dataNum*2:dataNum*3, 1] = np.random.randn(dataNum) + 8
X[dataNum*3:dataNum*4, 0] = np.random.randn(dataNum) + 8
X[dataNum*3:dataNum*4, 1] = np.random.randn(dataNum) + 8

plt.figure(1)
plt.plot(X[:,0], X[:,1], '*g')

N = X.shape[0]
K = 5
m = np.zeros((K,2))
Xlabel = np.zeros((N,1))
i = 0
cmode = ['*g', '*r', '*b', '*y', '*m']

#대표 벡터를 선택
while i < K:
    t = int(np.floor(np.random.rand(1) * N))
    if (X[t,:] != m[0,:]).all and (X[t,:] != m[1,:]).all:
        m[i,:] = X[t,:]
        plt.plot(m[i,0], m[i,1], "Dk")
        i += 1

plt.show()


for iteration in range(0,10,1):
    #각 데이터를 가까운 클러스터에 할당
    plt.figure(iteration+(K*10))
    Xlabel = np.zeros((1,N))

    for i in range(0,N,1):
        dist = np.zeros((1,K))
        for j in range(0,K,1):
            dist[0,j] = np.dot(X[i,:] - m[j,:], X[i,:] - m[j,:].T)
        Xlabel[0,i] = np.argmin(dist)

    #대표벡터를 다시계산
    for i in range(0,K,1):
        I = np.where(Xlabel == i)
        m[i,0] = np.mean(X[I[1], 0])
        m[i,1] = np.mean(X[I[1], 1])

    for i in range(0,K,1):
        c1 = np.where(Xlabel == i)
        plt.plot(X[c1[1], 0], X[c1[1], 1], cmode[i])

    for i in range(0,K,1):
        plt.plot(m[i,0], m[i,1], 'Dk')

    plt.show()